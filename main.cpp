#define SERVER_PORT			8080
#define BUFF_SIZE			4096

#include "main_header.hpp"
#include "conf/ParserConf.hpp"
#include "http/parsing_http.hpp"
#include "core/HttpWorker.hpp"

sig_atomic_t volatile g_running = 1;

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_running = 0;
		std::cerr << std::endl << "Received CTRL-C signal, stopping webserv..." << std::endl;
	}
}

int		main(int argc, char *argv[])
{
    // Argument checking ->
    if (argc != 2) {
        std::cout << "Usage : './webserv configuration_file'" << std::endl;
        return 0;
    }

    signal(SIGINT, &sig_handler);

    // Parsing ->
    ParserConf parser;
    std::vector<ServerInfo> conf;
    parser.parse(argv[1], &conf);
    
    // Server list ->
    std::map<int, ServerInfo> server_sockets;
    for (std::vector<ServerInfo>::iterator it = conf.begin(); it != conf.end(); it++)
        server_sockets.insert(std::make_pair(VirtualServer(it->get_listen()).get_sock(), *it));
    
    // Run http worker ->
    HttpWorker worker(server_sockets);
    worker.run();

    return 0;
}