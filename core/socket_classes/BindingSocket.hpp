#ifndef BINDING_SOCKET_HPP
# define BINDING_SOCKET_HPP

#include "SimpleSocket.hpp"
#include <netinet/in.h>


namespace ft {

class BindingSocket: public SimpleSocket
{
private:
    struct sockaddr_in address;
    BindingSocket(void);

public:
    BindingSocket(int domain, int type, int protocol,
        int family, int addr, int port);
    ~BindingSocket();
    struct sockaddr_in get_address();
};

}

#endif