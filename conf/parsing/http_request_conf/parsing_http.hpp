#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP
# include <iostream>
# include <fstream>
# include <map>

enum e_request_method
{
    GET,
    POST,
    DELETE,
    HEAD,
    OPTIONS,
    CONNECT,
    PUT,
    PATCH,
    TRACE
};


struct s_request_line
{
    std::string _method;
    std::string _url;
    std::string _version;
};

struct s_request
{
    s_request_line req_line;
    std::map<std::string, std::string> fields;
};

#endif