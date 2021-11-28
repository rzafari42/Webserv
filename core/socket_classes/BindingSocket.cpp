#include "BindingSocket.hpp"

ft::BindingSocket::BindingSocket(int domain, int type, int protocol,
    int family, int addr, int port) : ft::SimpleSocket(domain, type, protocol)
{
    address.sin_family = family;
    address.sin_addr.s_addr = addr;
    address.sin_port = htons( port );

    int opt = 1;
    
    if (setsockopt(get_socket(), SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(get_socket(), (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

ft::BindingSocket::~BindingSocket()
{

}

struct sockaddr_in ft::BindingSocket::get_address()
{
    return address;
};
