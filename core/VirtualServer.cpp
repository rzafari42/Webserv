#include "VirtualServer.hpp"

VirtualServer::VirtualServer( short p ) : port(p) {
    int                 opt = 1;
    struct sockaddr_in  server_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
        throw VirtualServerException("Can't create socket!", errno);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) == -1)
        throw VirtualServerException("Setsockopt failed!", errno);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(port);

    if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
        throw VirtualServerException("Fcntl failed!", errno);
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr) == -1)
        throw VirtualServerException("Bind failed!", errno);
    if (listen(server_socket, V_SERVER_BACKLOG) == -1)
        throw VirtualServerException("Listen failed!", errno);
}