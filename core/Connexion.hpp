#ifndef CONNEXION_HPP
# define CONNEXION_HPP

# include "../http/parsing_http.hpp"
# include "../http/HttpResponse.hpp"
# include "../main_header.hpp"

class Connexion {
    private:
        int             sock;
        std::string     request_content;
        Request         request;
        HttpResponse    response;
        fd_set*         active_read;
        fd_set*         active_write;
        int             written;

    public:
        Connexion( int server_socket, fd_set* r, fd_set* w ) : active_read(r), active_write(w) {
            socklen_t       size;
            struct sockaddr client_addr;

            size = sizeof(struct sockaddr*);

            sock = accept(server_socket, &client_addr, &size);
	        if (sock == -1)
                throw ConnexionException("Connexion failed!", errno);
            setRead();
        }
        ~Connexion() {}
        
        void setRead( void ) { std::cout << sock << std::endl; FD_SET(sock, active_read); }
        void setWrite( void ) { FD_SET(sock, active_write); }
        void unsetRead( void ) { FD_CLR(sock, active_read); }
        void unsetWrite( void ) { FD_CLR(sock, active_write); }

        int isReadReady( void ) { return FD_ISSET(sock, active_read); }
        int isWriteReady( void ) { return FD_ISSET(sock, active_write); }

        int             get_sock( void ) { return sock; }
        std::string     get_request_content( void ) { return request_content; }
        Request         get_request( void ) { return request; }
        Request*        get_request_ptr( void ) { return &request; }
        HttpResponse    get_response( void ) { return response; }
        int             getWritten( void ) { return written; }

        void app_request( char *buffer ) { request_content.append(buffer); }
        void request_parsing( char *buffer ) { request = req_parsing(buffer); }
        void init_response( ServerInfo &conf ) { response = HttpResponse(&request, &conf); }
        void setWritten( int yolo ) { written = yolo; }

        class ConnexionException : public std::exception 
        {
            private:
                std::string msg;
            public:
                ~ConnexionException() throw() {}
                ConnexionException(std::string m, int errcode) : msg(m + " : " + strerror(errcode)) {}
                virtual const char * what () const throw () { return msg.c_str(); }
        };
};

#endif