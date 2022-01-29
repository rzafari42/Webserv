/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:47:10 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/29 02:48:04 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "main_header.hpp"

class HttpResponse
{
    public:
        HttpResponse();
        HttpResponse(Request *req);
        ~HttpResponse();

        void set_status_code(int code) { _statusCode = code; };
        void set_reasonPhrase(std::string phrase) { _reasonPhrase = phrase; };
        void set_contentLength(int length) { _contentLength = length; };
        void set_content(std::string content) { _content = content; };

        std::string get_http_version() { return HTTP_VERSION; };
        int get_status_code() { return _statusCode; };
        std::string get_reasonPhrase() { return _reasonPhrase; };
        int get_contentLength() { return _contentLength; };
        std::string get_content() { return _content; };
        std::string getResponse() { return _response; };

        void requestParsingError(int code);

        void handle_get_method(Request *req);
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


        std::map<int, std::string> _error;
        std::vector<std::string> _implementedMethods;
        std::vector<std::string> _notImplementedMethods;
        int check_method_existence(std::string method);
        bool check_basic_error(Request *req);
};

#endif
