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
    Location( void ) {}
    ~Location() {}
    std::vector<std::string> getMethods() { return methods }
};


#endif 