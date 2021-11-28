#ifndef LISTENING_SOCKET_HPP
# define LISTENING_SOCKET_HPP

#include "BindingSocket.hpp"


namespace ft {

class ListeningSocket: public BindingSocket
{
private:
    ListeningSocket(void);

public:
    ListeningSocket(int domain, int type, int protocol, int family, int addr, int port,
        int backlog);
    ~ListeningSocket();
};

}

#endif