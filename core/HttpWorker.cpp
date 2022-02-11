#define BUFF_SIZE			8192

#include "HttpWorker.hpp"

//pour l'instant cette fonction affiche juste la requette qu'elle recoit
//ajouter parsing de la requette et tt le reste

void HttpWorker::acceptConnection( int server_socket, ServerInfo s_info ) {
    try {
        Connexion *c = new Connexion(server_socket, &active_read, &active_write);
        connexions.insert(std::pair<Connexion*, ServerInfo>(c, s_info));
    } catch (const std::exception& e) {
        e.what();
    }
}

bool HttpWorker::handleRead(Connexion *c, ServerInfo conf) {
    int     client_socket = c->get_sock();
    char	buffer[BUFF_SIZE + 1];
    bool    can_continue = true;
    Request req;

	memset(buffer, '\0', sizeof(buffer));
	if (recv(client_socket, buffer, BUFF_SIZE, 0) > 0) {
		c->app_request(buffer);
        req = req_parsing(buffer);
        
        std::map<std::string, std::string>::iterator it;
        it = req.get_fields().find("Content-Length");

        if (it != req.get_fields().end())
            std::cout << it->second << "*" << std::endl;
        else
            std::cout << "yeet" << std::endl;
        
        if (c->get_request().find("\r\n\r\n") != std::string::npos) {
            if (!req.get_method().compare("POST")) {
                if (it != req.get_fields().end()) {
                    std::cout << it->second << std::endl;
                }
            }
        } else {
            can_continue = false;
        }
    }

    if (can_continue) {
        std::cout << c->get_request() << std::endl;
	    fflush(stdout);
	    
	    HttpResponse res(&req, &conf);
	    std::string cont = res.getResponse();
	    write(client_socket , cont.c_str(), cont.length()); //Envoie de la reponse au client
	    close(client_socket);
	    printf("closing connection\n");
    }
    return can_continue;
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
                if (handleRead(c, it_c->second))
                    FD_CLR(c->get_sock(), &active_read);
            }
        }
    }
    
    virtual_servers.clear();
    connexions.clear();
    
    return ;
}