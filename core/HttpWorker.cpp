#define BUFF_SIZE			8192

#include "HttpWorker.hpp"

//pour l'instant cette fonction affiche juste la requette qu'elle recoit
//ajouter parsing de la requette et tt le reste
static void	*handle_connection(int client_socket, ServerInfo conf)
{
    char	buffer[BUFF_SIZE + 1];
    size_t	bytes_read;
    int		msg_size = 0;
    static int i = 0;
    memset(buffer, '\0', sizeof(buffer));
    while((bytes_read = recv(client_socket, buffer, BUFF_SIZE, 0)))
    {
        msg_size += bytes_read;
        if (msg_size > BUFF_SIZE - 1 || buffer[msg_size - 1] == '\n' || buffer[msg_size] == '\0')
            break;
    }
    //buffer[BUFF_SIZE]  = '\0';

    printf("REQUEST: \n%s\n", buffer);
    fflush(stdout);

    //Name file creation
    std::string namefile = "Request_";
    std::ostringstream s;
    s << i;
    namefile.append(s.str());
    namefile.append(".txt");
    i++;

    std::ofstream myfile;
    myfile.open(namefile.c_str(), std::ofstream::app);
    myfile << buffer; //Write the request in a file
    myfile.close();
    Request req = req_parsing(namefile);			//Parsing
    std::remove(namefile.c_str());

    HttpResponse res(&req, &conf);
    std::string cont = res.getResponse();
    write(client_socket , cont.c_str(), cont.length()); //Envoie de la reponse au client
    close(client_socket);
    printf("closing connection\n");
    return (NULL);
}

void HttpWorker::acceptConnection( int server_socket, ServerInfo s_info ) {
    try {
        Connexion *c = new Connexion(server_socket, &active_read, &active_write);
        connexions.insert(std::pair<Connexion*, ServerInfo>(c, s_info));
    } catch (const std::exception& e) {
        e.what();
    }
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
                handle_connection(c->get_sock(), it_c->second);
                FD_CLR(c->get_sock(), &active_read);
            }
        }
    }
    
    virtual_servers.clear();
    connexions.clear();
    
    return ;
}