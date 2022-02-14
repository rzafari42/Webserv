#define BUFF_SIZE			8192

#include "HttpWorker.hpp"

//pour l'instant cette fonction affiche juste la requette qu'elle recoit
//ajouter parsing de la requette et tt le reste

void HttpWorker::acceptConnection( int server_socket, ServerInfo s_info ) {
    try {
        c = new Connexion(server_socket, &active_read, &active_write);
        connexions.insert(std::pair<Connexion*, ServerInfo>(c, s_info));
    } catch (const std::exception& e) {
        e.what();
    }
}

bool HttpWorker::handleRead(Connexion *c, ServerInfo conf) {
    int     client_socket = c->get_sock();
    char	buffer[BUFF_SIZE + 1];
    bool    can_continue = true;
    int     len;

	memset(buffer, '\0', sizeof(buffer));
    len = recv(client_socket, buffer, BUFF_SIZE, 0); 
	if (len > 0) {
		c->app_request(buffer);
        c->request_parsing(buffer);
        
        std::map<std::string, std::string> mymap = c->get_request().get_fields();
        std::map<std::string, std::string>::iterator it;
        it = mymap.find("Content-Length");

        if (c->get_request_content().find("\r\n\r\n") != std::string::npos) {
            if (!c->get_request().get_method().compare("POST")) {
                if (it != mymap.end()) {
                    if ((int)c->get_request().get_body().size() > std::atoi((it->second).c_str())) {
                        can_continue = false;
                    }
                }
            }
        } else {
            can_continue = false;
        }
    }

    if (can_continue) {
        std::cout << c->get_request_content() << std::endl;
	    fflush(stdout);
	    
        c->init_response(conf);
        c->setWritten(0);
    
    }
    return can_continue;
}

bool HttpWorker::handleWrite(Connexion *c) {
    int w = c->getWritten();
    int len;
    int client_socket = c->get_sock();
    std::string cont = c->get_response().getResponse();
    int str_len = cont.length();

    len = write(client_socket , &(cont.c_str()[w]), cont.length()); //Envoie de la reponse au client

    c->setWritten(w + len);

    if (w + len >= str_len) {
        close(client_socket);
        printf("closing connection\n");
        return true;
    }
    return false;
}

void HttpWorker::run() {
    // FD_SETS
    fd_set available_read	= { 0 };
    fd_set available_write	= { 0 };

    // Initialise reading set with Server Sockets
    std::map<int, ServerInfo>::iterator it_s;
    std::map<Connexion*, ServerInfo>::iterator it_c;
    
    FD_ZERO(&active_read);
    FD_ZERO(&active_write);

    for (it_s = virtual_servers.begin(); it_s != virtual_servers.end(); it_s++)
        FD_SET(it_s->first, &active_read);

    // Main Loop
    while (true) {
        // Available files
        available_read = active_read;
        available_write = active_write;

        // Select
        if (select(FD_SETSIZE, &available_read, &available_write, NULL, NULL) == -1) {
            std::cerr << "Select failed: " << strerror(errno) << std::endl;
            return ;
        }
        
        // New connection
        for (it_s = virtual_servers.begin(); it_s != virtual_servers.end(); it_s++)
            if (FD_ISSET(it_s->first, &available_read))
                acceptConnection(it_s->first, it_s->second);

        // Handle connections
        for (it_c = connexions.begin(); it_c != connexions.end(); it_c++) {
            Connexion *c = it_c->first;
            if (c->isReadReady()) {
                if (handleRead(c, it_c->second)) {
                    c->unsetRead();
                    c->setWrite();
                }
            }
            if (c->isWriteReady()) {
                if (handleWrite(c))
                    c->unsetWrite();
            }
        }
    }
    
    virtual_servers.clear();
    connexions.clear();
    
    return ;
}