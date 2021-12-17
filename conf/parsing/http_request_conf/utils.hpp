#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>
# include <fstream>
# include <vector>
# include <map>
# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define REQUEST_LINE_FORMAT "Error: Header Request-Line bad format."
# define REQUEST_FIELD_FORMAT "Error: Header fields bad format."
# define REQUEST_FIELD_FORMAT_SPACE "Error: In Header fields. No space before field value."
# define METHOD_LOWERCASE "Error: In Header Request-Line. Method is in lowercase."
# define METHOD_HOST_MISSING "400 Bad Request"
# define PROTOCOL_VERSION "HTTP/1.1"
# include "parsing_http.hpp"

void struct_init(s_request *req)
{
    req->req_line._method.clear();
    req->req_line._url.clear();
    req->req_line._version.clear();
    req->fields.clear();
}

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

#endif