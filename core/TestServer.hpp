#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include "socket_classes/ListeningSocket.hpp"
#include <string.h>

namespace ft {

class TestServer: public ListeningSocket
{
private:
    char buffer[1024];
    int new_socket;
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 21\n\n<h1>Hello world!</h1>";
    TestServer(void);

public:
    TestServer(int addr, int port, int backlog);
    ~TestServer();
    void accepter();
    void handler();
    void responder();
    void launch();
};

}

#endif