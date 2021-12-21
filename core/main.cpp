#include "TestServer.hpp"

#define PORT 8080
#define ADDR INADDR_ANY

int main(void) {
    while (1) {
        ft::TestServer serv(ADDR, PORT, 3);
        serv.launch();
    }
    return 0;
}