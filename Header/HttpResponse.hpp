#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include "main_header.hpp"
# include "../conf/parsing/http_request_conf/parsing_http.hpp"
# include <algorithm>
# define HOME_PAGE_PATH "/index.html"
# define ERROR_404_PATH "/error404.html"
# define FILE_DELETED "/file_deleted.html"



class HttpResponse
{
    public:
        HttpResponse();
        HttpResponse(Request *req);
        ~HttpResponse();
        
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

        void requestParsingError(int code);

        void handle_get_method(Request *req);
        void handle_post_method(Request *req);
        void handle_delete_method(Request *req);
        void constructResponse();


    private:
        void initValues();
        void initErrorMap();
        void initMethods();

        int _statusCode;
        std::string _reasonPhrase;
        int _contentLength;
        std::string _content;
        std::string _contentType;
        std::string _response;


        std::map<int, std::string> _error;
        std::vector<std::string> _implementedMethods;
        std::vector<std::string> _notImplementedMethods;
        int check_method_existence(std::string method);
};

#endif