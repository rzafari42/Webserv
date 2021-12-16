#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>
# include <fstream>
# include <vector>
# include <map>
# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define UNCLOSED_BRACKET "Error: '}' missing"
# include "parsing_http.hpp"

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

#endif