/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:50:20 by simbarre          #+#    #+#             */
/*   Updated: 2022/02/10 01:37:42 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP

# include "../../../Header/main_header.hpp"
# define CGI_EXTENSION ".php"

class Request{
    public:
        Request();
        Request(const Request& src) : _method(src._method), _url(src._url), _version(src._version), _cgi(src._cgi), _contentType(src._contentType), _fields(src._fields), _body(src._body), _contentTypeArray(src._contentTypeArray),  _isErrorSyntax(src._isErrorSyntax), _isMultiPart(src._isMultiPart), _boundary(src._boundary) {};
        Request &operator=(const Request& rhs) {
            _method = rhs._method;
            _url = rhs._url;
            _version = rhs._version;
            _cgi = rhs._cgi;
            _contentType = rhs._contentType;
            _fields = rhs._fields;
            _body = rhs._body;
            _contentTypeArray = rhs._contentTypeArray;
            _isErrorSyntax = rhs._isErrorSyntax;
            _isMultiPart = rhs._isMultiPart;
            _boundary = rhs._boundary;
            return *this;
        }
        ~Request() {_fields.clear(); _body.clear(); _contentTypeArray.clear(); return;}
        void set_method(std::string str) {_method = str;}
        void set_url(std::string str) {_url = str;}
        void set_version(std::string str) {_version = str;}
        void set_cgi(std::string str){_cgi = str;}
        void set_contentType(std::string str){_contentType = str;};
        void set_fields(std::map<std::string, std::string> mp){_fields = mp;}
        void set_body(std::vector<std::string> str){_body = str;};
        void set_isErrorSyntax(void){_isErrorSyntax = true;};
        void set_isMultiPart(void) {_isMultiPart = true;};
        void set_Boundary(std::string str) {_boundary = str;};

        std::string get_method() {return _method;}
        std::string get_url() {return _url;}
        std::string get_version() {return _version;}
        std::string get_cgi() {return _cgi;}
        std::string get_contentType() {return _contentType;}
        std::map<std::string, std::string> get_fields() {return _fields;}
        std::vector<std::string> get_body() {return _body;}
        std::vector<std::string> get_contentTypeArray() { return _contentTypeArray;}
        bool get_isErrorSyntax() {return _isErrorSyntax;};
        bool get_isMultiPart() {return _isMultiPart;};

        std::string get_boundary() {return _boundary;};

        void initContentType();
        
        private:
            std::string _method;
            std::string _url;
            std::string _version;
            std::string _cgi;
            std::string _contentType;
            std::map<std::string, std::string> _fields;
            std::vector<std::string> _body;
            std::vector<std::string> _contentTypeArray;
            bool _isErrorSyntax;
            bool _isMultiPart;
            std::string			_boundary;

};

Request req_parsing(std::string av);

#endif
