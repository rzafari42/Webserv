#ifndef CONNEXION_HPP
# define CONNEXION_HPP

# include "../Header/main_header.hpp"

class Connexion {
    private:
        int     sock;
        fd_set* active_read;
        fd_set* active_write;

    public:
        Connexion( int server_socket, fd_set* r, fd_set* w ) : active_read(r), active_write(w) {
            socklen_t       size;
            struct sockaddr client_addr;

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

        int get_sock( void ) { return sock; }

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