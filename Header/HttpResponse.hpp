#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include "../conf/parsing/http_request_conf/parsing_http.hpp"

class HttpResponse
{
    public:
        HttpResponse() : _httpVersion("HTTP/1.1"), _statusCode(404), _reasonPhrase("Not Found"), _contentLength(0), _content(""), _response("") {};
        HttpResponse(Request *req);
        ~HttpResponse();

        void set_http_version(std::string version);
        void set_status_code(int code);
        void set_reasonPhrase(std::string phrase);
        void set_contentLength(int length);
        void set_content(std::string content);

        std::string get_http_version();
        int get_status_code();
        std::string get_reasonPhrase();
        int get_contentLength();
        std::string get_content();
        std::string getResponse();

        void handle_get_method(Request *req);
        void handle_post_method(Request *req);
        void handle_delete_method(Request *req);
        void constructResponse();


    private:
        std::string _httpVersion;
        int _statusCode;
        std::string _reasonPhrase;
        int _contentLength;
        std::string _content;
        std::string _response;

        int check_method_existence(std::string method);
        /*int return_error(int code);*/
};

#endif