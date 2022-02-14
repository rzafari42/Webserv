#ifndef HTTP_WORKER_HPP
# define HTTP_WORKER_HPP

# include "VirtualServer.hpp"
# include "Connexion.hpp"
# include "../conf/ServerInfo.hpp"
# include "../main_header.hpp"

class HttpWorker {
    private:
        std::map<int, ServerInfo> virtual_servers;
        std::map<Connexion*, ServerInfo> connexions;
        fd_set active_read;
        fd_set active_write;
        Connexion *c;

    public:
        HttpWorker(std::map<int, ServerInfo> s_sockets) : virtual_servers(s_sockets) {}
        ~HttpWorker() 
        {
            delete c;
        }

        void run( void );
        void acceptConnection( int server_socket, ServerInfo s_info );
        bool handleRead(Connexion *c, ServerInfo conf);
        bool handleWrite(Connexion *c);
};

#endif