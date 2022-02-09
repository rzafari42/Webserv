#ifndef VIRTUAL_SERVER_HPP
# define VIRTUAL_SERVER_HPP
# define V_SERVER_BACKLOG 100

# include "../Header/main_header.hpp"

class VirtualServer {
    private:
        int sock;
        int port;

    public:
        
        VirtualServer( short p ) : port(p) {
            int                 opt = 1;
            struct sockaddr_in  server_addr;

            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
                throw VirtualServerException("Can't create socket!", errno);
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) == -1)
                throw VirtualServerException("Setsockopt failed!", errno);

            server_addr.sin_family      = AF_INET;
            server_addr.sin_addr.s_addr = INADDR_ANY;
            server_addr.sin_port        = htons(port);

            if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
                throw VirtualServerException("Fcntl failed!", errno);
            if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
                throw VirtualServerException("Bind failed!", errno);
            }
            if (listen(sock, V_SERVER_BACKLOG) == -1)
                throw VirtualServerException("Listen failed!", errno);
        }
        ~VirtualServer() {}

        int get_sock( void ){ return sock; }
        int get_port( void ){ return port; }
        
        class VirtualServerException : public std::exception 
        {
            private:
                std::string msg;
            public:
                ~VirtualServerException() throw() {}
                VirtualServerException(std::string m, int errcode) : msg(m + " : " + strerror(errcode)) {}
                virtual const char * what () const throw () { return msg.c_str(); }
        };

};

#endif