#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP
# include <iostream>
# include <fstream>
# include <map>

enum request_method
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


struct request_line
{
    std::string _method;
    std::string _url;
    std::string _version;
};

class Request
{
    public:
        Request();
        Request(const Request & src);
        ~Request();
        Request & operator=(const Request & rhs);


    private:

        std::map<std::string, std::string> _Header_Content;
};

#endif