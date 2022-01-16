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
    std::vector<std::string> get_methods( void ) { return methods }

    // setters
    void set_root(std::string str) {
        root = str;
    }
};


#endif 