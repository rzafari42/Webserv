#ifndef SERVER_INFO_HPP
# define SERVER_INFO_HPP
# include <iostream>
# include <vector>
# include "Location.hpp"

class ServerInfo
{
private:
    int nb_closing_br; 
    std::string listen;
    std::string root;
    std::string index;
    std::string autoindex;
    std::string error_page;
    std::string server_name;
    size_t client_max_body_size;
    std::vector<Location::Location> locations;

public:
    // constructor/destructor
    ServerInfo( void ) : nb_closing_br(0) {}
    ~ServerInfo() {}
    
    //getters
    std::vector<Location::Location> get_locations( void ) {
        return locations;
    }

    int get_nb_closing_br( void ) {
        return nb_closing_br;
    }


    //setters
    void inc_closing_br( void ) {
        nb_closing_br++;
    }
    
    void dec_closing_br( void ) {
        nb_closing_br--;
    }
    
};



#endif 