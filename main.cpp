#define SERVER_PORT			8080
#define BUFF_SIZE			4096

#include "Header/main_header.hpp"

int		main(int argc, char *argv[])
{
    // Argument checking ->
    if (argc != 2) {
        std::cout << "Usage : './webserv configuration_file'" << std::endl;
        return 0;
    }

    // Parsing ->
    ParserConf parser;
    std::vector<ServerInfo> conf;
    parser.parse(argv[1], &conf);
    
    // Server list ->
    std::map<int, ServerInfo> server_sockets;
    for (std::vector<ServerInfo>::iterator it = conf.begin(); it != conf.end(); it++)
        server_sockets.insert(std::make_pair(VirtualServer(it->get_listen()).get_sock(), *it));
    
    // Run http worker ->


    return 0;
}