#ifndef HTTP_WORKER_HPP
# define HTTP_WORKER_HPP

# include "../Header/main_header.hpp"

class HttpWorker {
    private:
        std::map<int, ServerInfo> virtual_servers;
        std::map<Connexion*, ServerInfo> connexions;
        fd_set active_read;
        fd_set active_write;

    public:
        HttpWorker(std::map<int, ServerInfo> s_sockets) : virtual_servers(s_sockets) {}
        ~HttpWorker() {}

        void run( void );
        void acceptConnection( int server_socket, ServerInfo s_info );
        bool handleRead(Connexion *c, ServerInfo conf);
};

#endif