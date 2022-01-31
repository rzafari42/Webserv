#ifndef SERVER_INFO_HPP
# define SERVER_INFO_HPP
# include <iostream>
# include <vector>
# include "Location.hpp"

class ServerInfo
{
private:
    std::size_t listen;
    std::string root;
    std::vector<std::size_t> error_code;
    std::vector<std::string> error_path;
    std::string server_name;
    size_t client_max_body_size;
    std::vector<Location> locations;

public:
    // constructor/destructor
    ServerInfo( void ) : listen(0), client_max_body_size(0) {
        root.clear();
        error_path.clear();
        error_code.clear();
        server_name.clear();
        locations.clear();
    }
    ~ServerInfo() {}

    //getters
    std::vector<Location> get_locations( void ) { return locations; }

    std::size_t get_listen( void ) const { return listen; }

    std::string get_root( void ) { return root; }

    std::vector<std::size_t> get_error_code( void ) { return error_code; }

    std::vector<std::string> get_error_path( void ) { return error_path; }

    std::string get_server_name( void ) { return server_name; }

    size_t get_client_max_body_size( void ) { return client_max_body_size; }


    //setters
    void set_listen( std::size_t n ) { listen = n; }

    void set_root( std::string str ) { root = str; }

    void add_error_code( std::size_t n ) { error_code.push_back(n); }
    
    void add_error_path( std::string str ) { error_path.push_back(str); }

    void set_server_name( std::string str ) { server_name = str; }

    void set_client_max_body_size( size_t n ) { client_max_body_size = n; }

    void add_location( Location l ) { locations.push_back(l); }

    friend bool operator<(const ServerInfo& t1, const ServerInfo& t2)
    {
        return (t1.get_listen() < t2.get_listen());
    }
};



#endif
