#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP
# include <iostream>
# include <fstream>
# include <sstream>

class HttpResponse
{
    public:
        HttpResponse() : httpVersion("HTTP/1.1"), statusCode(404), reasonPhrase("Not Found"), contentLength(0) {};
        HttpResponse(std::string source);
        void setstatusCode(int code);
        ~HttpResponse();

        std::string getResponse();

    private:
        std::string httpVersion;
        int statusCode;
        std::string reasonPhrase;
        int contentLength;
        std::string content;
        std::string response;
};

#endif