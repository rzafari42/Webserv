#include "ListeningSocket.hpp"

ft::ListeningSocket::ListeningSocket(int domain, int type, int protocol, int family, int addr, int port,
    int backlog) : ft::BindingSocket(domain, type, protocol, family, addr, port)
{
    if (listen(get_socket(), backlog) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

ft::ListeningSocket::~ListeningSocket()
{

}