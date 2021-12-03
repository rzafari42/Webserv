#include <iostream>
#include <fstream>
#include <vector>
#define EMPTY "Error: Not enough arguments"
#define OPENING_FAILURE "Error: File is not accessible in reading mode"
#define SERVER_POSITION "Error: Server block not declared at top"
#define LISTEN_EMPTY "Error: 'listen' directive exists but has no value"
#define ROOT_EMPTY "Error: 'root' directive exists but has no value"
#define INDEX_EMPTY "Error: 'index' directive exists but has no value"
#define ERROR_PAGE_EMPTY "Error: 'error_page' directive exists but has no value"
#define SERVER_NAME_EMPTY "Error: 'server_name' directive exists but has no value"

struct s_location {
    std::string index;
    std::vector<std::string> methods;
};

struct s_server
{
    size_t nb_server;
    size_t nb_location;
    std::string listen;
    std::string root;
    std::string index;
    std::string error_page;
    std::string server_name;
    std::string location;
    size_t      client_max_body_size;
    std::string autoindex;
    std::string methods;
};

void struct_init(s_server *conf)
{
    conf->nb_server = 0;
    conf->nb_location = 0;
    conf->client_max_body_size = 0;
    conf->listen.clear();
    conf->server_name.clear();
    conf->error_page.clear();
    conf->location.clear();
    conf->autoindex.clear();
    conf->index.clear();
    conf->root.clear();
}

int error(std::string code)
{
    std::cout << code << std::endl;
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

void print_conf_struct(std::vector<s_server> conf)
{
    std::vector<s_server>::iterator it = conf.begin();
    std::vector<s_server>::iterator ite = conf.end();

    while (it != ite)
    {
        std::cout << "Server: " << it->nb_server << std::endl;
        std::cout << "Location: " << it->nb_location << std::endl;
        std::cout << "Client_max_body_size: " << it->client_max_body_size << std::endl;
        std::cout << "Listen: " << it->listen << std::endl;
        std::cout << "Server_name: " << it->server_name << std::endl;
        std::cout << "Error_page: " << it->error_page << std::endl;
        std::cout << "Index: " << it->index << std::endl;
        std::cout << "Root: " << it->root << std::endl;
        std::cout << "Location: " << it->location << std::endl;
        std::cout << "Autoindex: " << it->autoindex << std::endl;
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
    std::cout << "Location: " << conf->location << std::endl;
    std::cout << "Autoindex: " << conf->autoindex << std::endl;
    std::cout << std::endl;
}