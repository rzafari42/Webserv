#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <iostream>
# include <vector>

class Location
{
private:
    std::string root;
    std::string index;
    std::string autoindex;
    std::string error_page;
    size_t client_max_body_size;
    std::vector<std::string> methods;
public:
    // constructor/ destructor
    Location( void ) {}
    ~Location() {}

    // getters
    std::vector<std::string> get_methods( void ) { return methods; }

    std::string get_root( void ) {
        return root;
    }

    std::string get_index( void ) {
        return index;
    }

    std::string get_autoindex( void ) {
        return autoindex;
    }

    std::string get_error_page( void ) {
        return error_page;
    }

    size_t get_client_max_body_size( void ) {
        return client_max_body_size;
    }

    // setters
    void set_root( std::string str ) {
        root = str;
    }

    void set_index( std::string str ) {
        index = str;
    }

    void set_autoindex( std::string str ) {
        autoindex = str;
    }

    void set_error_page( std::string str ) {
        error_page = str;
    }

    void set_client_max_body_size( size_t n ) {
        client_max_body_size = n;
    }
};


#endif
