#ifndef HTTP_WORKER_HPP
# define HTTP_WORKER_HPP

# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

class HttpWorker {
    private:
        std::map<int, ServerInfo> server_sockets;
        std::map<int, ServerInfo> client_sockets;
        fd_set active_read;
        fd_set active_write;

    public:
        HttpWorker(std::map<int, ServerInfo> s_sockets) : server_sockets(s_sockets) {}
        ~HttpWorker() {}
        void run( void );
};

#endif