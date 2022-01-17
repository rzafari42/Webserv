#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>
# include <fstream>
# include <vector>
# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define SERVER_POSITION "Error: Server block not declared at top"
# define LISTEN_EMPTY "Error: In Server: 'listen' directive exists but has no value"
# define ROOT_EMPTY "Error: In Server: 'root' directive exists but has no value"
# define INDEX_EMPTY "Error: In Server: 'index' directive exists but has no value"
# define ERROR_PAGE_EMPTY "Error: In Server: 'error_page' directive exists but has no value"
# define SERVER_NAME_EMPTY "Error: In Server: 'server_name' directive exists but has no value"
# define CLIENT_MAX_BODY_SIZE_EMPTY "Error: In Server: 'client_max_body_size' directive exists but has no value"
# define AUTOINDEX_EMPTY "Error: In Server: 'autoindex' directive exists but has no value"
# define LOCATION_ROOT_EMPTY "Error: In Location: 'root' directive exists but has no value"
# define LOCATION_INDEX_EMPTY "Error: In Location: 'index' directive exists but has no value"
# define LOCATION_AUTOINDEX_EMPTY "Error: In Location: 'autoindex' directive exists but has no value"
# define LOCATION_ERROR_PAGE_EMPTY "Error: In Location: 'error_page' directive exists but has no value"
# define LOCATION_CLIENT_MAX_BODY_SIZE_EMPTY "Error: In Location: 'client_max_body_size' directive exists but has no value"
# define LOCATION_METHODS_EMPTY "Error: In Location: 'methods' directive exists but has no value"
# define UNCLOSED_BRACKET "Error: '}' missing"
# include "ServerInfo.hpp"
# include "Location.hpp"

int error(std::string str)
{
    std::cout << str << std::endl;
    return -1;
}

void printlines(std::vector<std::vector<std::string> > s)
{
    int j;
    std::vector<std::vector<std::string> >::iterator it = s.begin();
    std::vector<std::vector<std::string> >::iterator ite = s.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;

    while (it != ite)
    {
        it_s = it->begin();
        ite_s = it->end();
        while(it_s != ite_s)
        {
            std::cout << *it_s;
            it_s++;
            if (it_s != ite_s)
                std::cout << " ";
        }
        std::cout << std::endl;
        it++;
    }
}

void print_location_methods_struct(std::vector<std::string> conf)
{
    std::vector<std::string>::iterator it = conf.begin();
    std::vector<std::string>::iterator ite = conf.end();

    std::cout << "Location Methods: " << std::endl;
    while (it != ite)
    {
        std::cout << " -" << *it << std::endl;
        it++;
    }

}

void print_conf_struct(std::vector<ServerInfo> conf)
{
    std::vector<ServerInfo>::iterator it = conf.begin();
    std::vector<ServerInfo>::iterator ite = conf.end();


    while (it != ite)
    {
        std::cout << "Client_max_body_size: " << it->get_client_max_body_size() << std::endl;
        std::cout << "Listen: " << it->get_listen() << std::endl;
        std::cout << "Server_name: " << it->get_server_name() << std::endl;
        std::cout << "Error_page: " << it->get_error_page() << std::endl;
        std::cout << "Index: " << it->get_index() << std::endl;
        std::cout << "Root: " << it->get_root() << std::endl;
        std::cout << "Autoindex: " << it->get_autoindex() << std::endl;

        std::vector<Location> vec_loc = it->get_locations();

        std::vector<Location>::iterator it_loc = vec_loc.begin();
        std::vector<Location>::iterator ite_loc = vec_loc.end();
        while (it_loc != ite_loc)
        {
            std::cout << "Location/root: " << it_loc->get_root() << std::endl;
            std::cout << "Location/index: " << it_loc->get_index() << std::endl;
            std::cout << "Location/autoindex: " << it_loc->get_autoindex() << std::endl;
            std::cout << "Location/error_page: " << it_loc->get_error_page() << std::endl;
            std::cout << "Location/client_max_body_size: " << it_loc->get_client_max_body_size() << std::endl;
            print_location_methods_struct(it_loc->get_methods());
            it_loc++;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        it++;
    }
}


#endif
