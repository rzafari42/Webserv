#ifndef VIRTUAL_SERVER_HPP
# define VIRTUAL_SERVER_HPP
# define V_SERVER_BACKLOG 100

class VirtualServer {
    private:
        int sock;
        int port;

    public:
        VirtualServer( int p );
        ~VirtualServer() {}
        int get_sock( void ){ return sock; }
        int get_port( void ){ return port; }
        class VirtualServerException : public std::exception 
        {
            public:
                virtual ~VirtualServerException() throw() {return ;}
                VirtualServerException(std::string msg, int errcode);
                virtual const char * what () const throw () {
                    return (msg + " : " + errcode).c_str();
                }
        };

};

#endif