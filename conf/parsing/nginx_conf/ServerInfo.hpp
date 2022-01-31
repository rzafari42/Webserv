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
    std::string error_page;
    std::string server_name;
    size_t client_max_body_size;
    std::vector<Location> locations;

public:
    // constructor/destructor
    ServerInfo( void ) : listen("0.0.0.0:8080"), client_max_body_size(0) {
    }
    ~ServerInfo() {}

    //getters
    std::vector<Location> get_locations( void ) {
        return locations;
    }

    std::string get_listen( void ) const {
        if (!listen.empty())
            return listen;
        return (NULL);
    }

    std::string get_root( void ) {
        return root;
    }

    std::string get_error_page( void ) {
        return error_page;
    }

    std::string get_server_name( void ) {
        return server_name;
    }

    size_t get_client_max_body_size( void ) {
        return client_max_body_size;
    }


    //setters
    void set_listen( std::string str ) {
        listen = str;
    }

    void set_root( std::string str ) {
        root = str;
    }

    void set_error_page( std::string str ) {
        error_page = str;
    }

    void set_server_name( std::string str ) {
        server_name = str;
    }

    void set_client_max_body_size( size_t n ) {
        client_max_body_size = n;
    }

    void add_location( Location l ) {
        locations.push_back(l);
    }

    friend bool operator<(const ServerInfo& t1, const ServerInfo& t2)
    {
        return (t1.get_listen() < t2.get_listen());
    }
};

#endif
