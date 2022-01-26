#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP
# include <iostream>
# include <fstream>
# include <map>

class Request{

    public:
        Request() {_method.clear(); _url.clear(); _version.clear();};
        Request(const Request& src) : _method(src._method), _url(src._url), _version(src._version) {};
        Request &operator=(const Request& rhs) {
            _method = rhs._method;
            _url = rhs._url;
            _version = rhs._version;
            _fields = rhs._fields;
            return *this;
        }
        ~Request() {return;}
        void set_method(std::string str) {_method = str;}
        void set_url(std::string str) {_url = str;}
        void set_version(std::string str) {_version = str;}
        void set_fields(std::map<std::string, std::string> mp){_fields = mp;}
        std::string get_method() {return _method;}
        std::string get_url() {return _url;}
        std::string get_version() {return _version;}
        std::map<std::string, std::string> get_fields() {return _fields;}

        private:
            std::string _method;
            std::string _url;
            std::string _version;
            std::map<std::string, std::string> _fields;
};

Request req_parsing(std::string av);

#endif