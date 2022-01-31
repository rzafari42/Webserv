#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <vector>
//# include "../Header/HttpResponse.hpp"
# define WEBFILE_PATH "www"
# define CGI_EXTENSION ".php"


class Request{

    public:
        Request() {_method.clear(); _url.clear(); _version.clear(); _body.clear(); _isErrorSyntax = false;};
        Request(const Request& src) : _method(src._method), _url(src._url), _version(src._version) {};
        Request &operator=(const Request& rhs) {
            _method = rhs._method;
            _url = rhs._url;
            _version = rhs._version;
            _fields = rhs._fields;
            return *this;
        }
        ~Request() {_fields.clear(); _body.clear(); return;}
        void set_method(std::string str) {_method = str;}
        void set_url(std::string str) {_url = WEBFILE_PATH + str;}
        void set_version(std::string str) {_version = str;}
        void set_cgi(std::map<std::string, std::string> mp){_cgi = mp;}
        void set_fields(std::map<std::string, std::string> mp){_fields = mp;}
        void set_body(std::vector<std::string> str){_body = str;};
        void set_isErrorSyntax(void){_isErrorSyntax = true;};

        std::string get_method() {return _method;}
        std::string get_url() {return _url;}
        std::string get_version() {return _version;}
        std::map<std::string, std::string> get_cgi() {return _cgi;}
        std::map<std::string, std::string> get_fields() {return _fields;}
        std::vector<std::string> get_body() {return _body;}
        bool get_isErrorSyntax() {return _isErrorSyntax;};

        private:
            std::string _method;
            std::string _url;
            std::string _version;
            std::map<std::string, std::string> _cgi;
            std::map<std::string, std::string> _fields;
            std::vector<std::string> _body;
            bool _isErrorSyntax;
};

Request req_parsing(std::string av);

#endif