#include "TestServer.hpp"

ft::TestServer::TestServer(int addr, int port, int backlog) : 
        ft::ListeningSocket(AF_INET, SOCK_STREAM, 0, AF_INET, addr, port, backlog) {
}

ft::TestServer::~TestServer() {
}

void ft::TestServer::accepter() {
    int serv_socket = get_socket();
    struct sockaddr_in addr = get_address();
    int addr_len = sizeof(addr);

    if ((new_socket = accept(serv_socket, (struct sockaddr *)&addr, (socklen_t*)&addr_len))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    read( new_socket , buffer, 1024);
}

void ft::TestServer::handler() {
    printf("%s\n", buffer);
}

void ft::TestServer::responder() {
    send(new_socket , hello, strlen(hello) , 0);
}

void ft::TestServer::launch() {
    accepter();
    handler();
    responder();
}
