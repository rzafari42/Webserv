#include "SimpleSocket.hpp"

ft::SimpleSocket::SimpleSocket(int domain, int type, int protocol)
{
    if (!(socket_fd = socket(domain, type, protocol))) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
}

ft::SimpleSocket::~SimpleSocket()
{
    close(socket_fd);
}

int ft::SimpleSocket::get_socket(void) {
    return socket_fd;
}