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
# include "parsing_nginx.hpp"

void struct_init(s_server *conf)
{
    conf->nb_closing_br = 0;
    conf->nb_server = 0;
    conf->nb_location = 0;
    conf->client_max_body_size = 1;
    conf->listen.clear();
    conf->server_name.clear();
    conf->error_page.clear();
    conf->location.root = "html";
    conf->location.client_max_body_size = 1;
    conf->location.index = "index.html";
    conf->location.autoindex = "off";
    conf->location.error_page.clear();
    conf->location.methods.clear();
    conf->autoindex = "off";
    conf->index = "index.html";
    conf->root = "html";
}

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

void print_conf_struct(std::vector<s_server> conf)
{
    std::vector<s_server>::iterator it = conf.begin();
    std::vector<s_server>::iterator ite = conf.end();

    while (it != ite)
    {
        std::cout << "nb_Closing_bracket: " << it->nb_server << std::endl;
        std::cout << "nb_Server: " << it->nb_server << std::endl;
        std::cout << "nb_Location: " << it->nb_location << std::endl;
        std::cout << "Client_max_body_size: " << it->client_max_body_size << std::endl;
        std::cout << "Listen: " << it->listen << std::endl;
        std::cout << "Server_name: " << it->server_name << std::endl;
        std::cout << "Error_page: " << it->error_page << std::endl;
        std::cout << "Index: " << it->index << std::endl;
        std::cout << "Root: " << it->root << std::endl;
        std::cout << "Location index: " << it->location.index << std::endl;
        std::cout << "Autoindex: " << it->autoindex << std::endl;
        std::cout << "Location/root: " << it->location.root << std::endl;
        std::cout << "Location/index: " << it->location.index << std::endl;
        std::cout << "Location/autoindex: " << it->location.autoindex << std::endl;
        std::cout << "Location/error_page: " << it->location.error_page << std::endl;
        std::cout << "Location/client_max_body_size: " << it->location.client_max_body_size << std::endl;
        
        print_location_methods_struct(it->location.methods);
        std::cout << std::endl;
        std::cout << std::endl;
        it++;
    }
}

void print_conf_struct(s_server *conf)
{
    std::cout << "Server: " <<  conf->nb_server << std::endl;
    std::cout << "Location: " << conf->nb_location << std::endl;
    std::cout << "Client_max_body_size: " << conf->client_max_body_size << std::endl;
    std::cout << "Listen: " << conf->listen << std::endl;
    std::cout << "Server_name: " << conf->server_name << std::endl;
    std::cout << "Error_page: " << conf->error_page << std::endl;
    std::cout << "Index: " << conf->index << std::endl;
    std::cout << "Root: " << conf->root << std::endl;
    std::cout << "Location index: " << conf->location.index << std::endl;
    std::cout << "Autoindex: " << conf->autoindex << std::endl;
    std::cout << std::endl;
}

#endif