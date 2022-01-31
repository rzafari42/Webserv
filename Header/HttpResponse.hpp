#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <dirent.h>
#include "../conf/parsing/http_request_conf/parsing_http.hpp"
#include "../conf/parsing/nginx_conf/ServerInfo.hpp"
# include <algorithm>
# define HOME_PAGE_PATH "/index.html"
# define ERROR_400_PATH "/error400.html"
# define ERROR_404_PATH "/error404.html"
# define ERROR_411_PATH "/error411.html"
# define ERROR_505_PATH "/error505.html"
# define ERROR_310_PATH "/error310.html"

# define HTTP_VERSION "HTTP/1.1"

# define FILE_DELETED "/file_deleted.html"



class HttpResponse
{
    public:
        HttpResponse();
        HttpResponse(Request *req, ServerInfo *conf);
        ~HttpResponse();
        
        void set_status_code(int code) { _statusCode = code; };
        void set_reasonPhrase(std::string phrase) { _reasonPhrase = phrase; };
        void set_contentLength(int length) { _contentLength = length; };
        void set_content(std::string content) { _content = content; };
        void set_redirectLoop() { _redirectLoop = true; };

        std::string get_http_version() { return HTTP_VERSION; };
        int get_status_code() { return _statusCode; };
        std::string get_reasonPhrase() { return _reasonPhrase; };
        int get_contentLength() { return _contentLength; };
        std::string get_content() { return _content; };
        std::string getResponse() { return _response; };
        bool get_redirectLoop() { return _redirectLoop; };

        bool CountLocRedirect(std::map<std::string, int> *mp, std::string uri);

        void requestParsingError(int code);
        int check_redirection(Request *req, ServerInfo *conf);

        void handle_get_method(Request *req, ServerInfo *conf);
        void handle_post_method(Request *req);
        void handle_delete_method(Request *req);

        void redirection(Request *req);
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
        bool _redirectLoop;


        std::map<int, std::string> _error;
        std::vector<std::string> _implementedMethods;
        std::vector<std::string> _notImplementedMethods;
        int check_method_existence(std::string method);
        bool check_basic_error(Request *req);
};

#endif