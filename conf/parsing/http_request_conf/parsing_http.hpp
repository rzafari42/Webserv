/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:50:20 by simbarre          #+#    #+#             */
/*   Updated: 2022/02/03 07:40:48 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP

# include "../../../Header/main_header.hpp"
# define CGI_EXTENSION ".php"

class Request{
    public:
        Request() {_method.clear(); _url.clear(); _version.clear(); _cgi.clear(); _fields.clear(); _body.clear(); _isErrorSyntax = false;};
        Request(const Request& src) : _method(src._method), _url(src._url), _version(src._version), _cgi(src._cgi), _fields(src._fields), _body(src._body), _isErrorSyntax(src._isErrorSyntax){};
        Request &operator=(const Request& rhs) {
            _method = rhs._method;
            _url = rhs._url;
            _version = rhs._version;
            _cgi = rhs._cgi;
            _fields = rhs._fields;
            _body = rhs._body;
            _isErrorSyntax = rhs._isErrorSyntax;
            return *this;
        }
        ~Request() {_fields.clear(); _body.clear(); return;}
        void set_method(std::string str) {_method = str;}
        void set_url(std::string str) {_url = str;}
        void set_version(std::string str) {_version = str;}
        void set_cgi(std::string str){_cgi = str;}
        void set_fields(std::map<std::string, std::string> mp){_fields = mp;}
        void set_body(std::vector<std::string> str){_body = str;};
        void set_isErrorSyntax(void){_isErrorSyntax = true;};

        std::string get_method() {return _method;}
        std::string get_url() {return _url;}
        std::string get_version() {return _version;}
        std::string get_cgi() {return _cgi;}
        std::map<std::string, std::string> get_fields() {return _fields;}
        std::vector<std::string> get_body() {return _body;}
        bool get_isErrorSyntax() {return _isErrorSyntax;};

        private:
            std::string _method;
            std::string _url;
            std::string _version;
            std::string _cgi;
            std::map<std::string, std::string> _fields;
            std::vector<std::string> _body;
            bool _isErrorSyntax;
};

Request req_parsing(std::string av);

#endif
