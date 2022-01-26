#include "../ParserConf.hpp"

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


int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Parser needs argument" << std::endl;
                return 1;
    }
    std::vector<ServerInfo> serv_info;
    ParserConf parser;
    parser.parse(av[1], &serv_info);
    print_conf_struct(serv_info);
    return 0;
}
