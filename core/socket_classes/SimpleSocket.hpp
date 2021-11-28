#ifndef SIMPLE_SOCKET_HPP
# define SIMPLE_SOCKET_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


namespace ft {

class SimpleSocket
{
private:
    int socket_fd;
    SimpleSocket(void);

protected:

public:
    SimpleSocket(int domain, int type, int protocol);
    ~SimpleSocket();
    int get_socket(void);
};

}

#endif