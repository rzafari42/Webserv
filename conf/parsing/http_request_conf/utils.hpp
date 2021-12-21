#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>
# include <fstream>
# include <vector>
# include <map>
# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define REQUEST_LINE_FORMAT "Error: Header Request-Line bad format."
# define REQUEST_LINE_FORMAT_CRLF "Error: Header Request-Line bad format. CRLF Missing !"
# define REQUEST_FIELD_FORMAT "Error: Header fields bad format."
# define REQUEST_FIELD_FORMAT_SPACE "Error: In Header fields. No space before field value."
# define REQUEST_FIELD_FORMAT_CRLF "Error: Header fields bad format. CRLF Missing !"
# define METHOD_LOWERCASE "Error: In Header Request-Line. Method is in lowercase."
# define METHOD_HOST_MISSING "400 Bad Request"
# define PROTOCOL_VERSION "HTTP/1.1"
# define CRLF "\r\n"
# define CR '\r'
# define LF '\n'
# include "parsing_http.hpp"

int error(std::string str)
{
    std::cout << str << std::endl;
    return -1;
}

void print_map(std::map<std::string, std::string> mymap)
{
    std::map<std::string,std::string>::iterator it;

    std::cout << "Map contains:\n";
    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << ": " << it->second << '\n';
}

#endif