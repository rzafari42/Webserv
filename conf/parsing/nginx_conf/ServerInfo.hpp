#ifndef SERVER_INFO_HPP
# define SERVER_INFO_HPP
# include <iostream>
# include <vector>
# include "Location.hpp"

class ServerInfo
{
private:
    std::string listen;
    std::string root;
    std::string index;
    std::string autoindex;
    std::string error_page;
    std::string server_name;
    size_t client_max_body_size;
    std::vector<Location::Location> locations;

public:
    ServerInfo( void ) {}
    ~ServerInfo() {}
    std::vector<Location::Location> getLocations {
        return locations;
    }
};



#endif 