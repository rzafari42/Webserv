/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:19:15 by rzafari           #+#    #+#             */
/*   Updated: 2022/02/10 22:30:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Header/main_header.hpp"

Request::Request()
{
    _method.clear();
    _url.clear();
    _version.clear();
    _cgi.clear();
    _fields.clear();
    _body.clear();
    _isErrorSyntax = false;
    _contentType.clear();
    initContentType();
}

void Request::initContentType()
{
    _contentTypeArray.push_back("text/plain");
    _contentTypeArray.push_back("text/html");
    _contentTypeArray.push_back("text/css");
    _contentTypeArray.push_back("text/javascript");

    _contentTypeArray.push_back("image/gif");
    _contentTypeArray.push_back("image/png");
    _contentTypeArray.push_back("image/jpeg");
    _contentTypeArray.push_back("image/bmp");
    _contentTypeArray.push_back("image/webp");

    _contentTypeArray.push_back("audio/midi");
    _contentTypeArray.push_back("audio/mpeg");
    _contentTypeArray.push_back("audio/webm");
    _contentTypeArray.push_back("audio/ogg");
    _contentTypeArray.push_back("audio/wav");

    _contentTypeArray.push_back("video/webm");
    _contentTypeArray.push_back("video/ogg");

    _contentTypeArray.push_back("application/octet-stream");
    _contentTypeArray.push_back("application/pkcs12");
    _contentTypeArray.push_back("application/vnd.mspowerpoint");
    _contentTypeArray.push_back("application/xhtml+xml");
    _contentTypeArray.push_back("application/xml");
    _contentTypeArray.push_back("application/pdf");
}

int check_format_rqline(std::string s, Request *req)
{
    unsigned long i = 0;
    int nb_space = 0;
    int nb_arg = 0;

   if (s.find('\n') == std::string::npos)   //cant find '\r' ??
        return error(REQUEST_LINE_FORMAT_CRLF, 1, req);
    s.erase(s.size() - 2);
    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
            i++;
        nb_arg += 1;
        if (i < s.length() && s[i] != CR)
            nb_space += 1;
        i++;
    }
    if (nb_space == 2 && nb_arg == 3)
        return 0;
    return error(REQUEST_LINE_FORMAT, 1, req);
}

int check_format_rqfield(std::string s, Request *req)
{
    unsigned long i = 0;
    int semi_colon = 0;
    int nb_arg = 0;

    if (s.find("\n") == std::string::npos) //cant find '\r' ??
        return error(REQUEST_FIELD_FORMAT_CRLF, 1, req);
    s.erase(s.size() - 1);
    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
        {
            if (s[i] == ':' && semi_colon == 0)
            {
                semi_colon += 1;
                if (!isspace(s[ i + 1]))
                    return error(REQUEST_FIELD_FORMAT_SPACE, 1, req);
                break;
            }
            i++;
        }
        if (s[i] != ':')
            nb_arg += 1;
        i++;
    }
    if (semi_colon == 1 && nb_arg >= 2)
        return 0;
    return error(REQUEST_FIELD_FORMAT, 1, req);
}

int check_cgi(Request *req, std::string &cgi)
{
    std::string url = req->get_url();
    std::size_t pos = 0;

    pos = url.find(CGI_EXTENSION);
    if (pos != std::string::npos && url.find("?") != std::string::npos)
    {
        while (url[pos] != '?' && pos != url.size())
            pos++;
        if (pos == url.size())
            return -1;
        pos++;
        while (pos != url.size())
        {
            cgi.push_back(url[pos]);
            pos++;
        }
    }
    return 0;
}

int catch_request_line(const std::string s, Request *req, std::string &cgi) //Format: Method Request-URI HTTP-Version CRLF
{
    unsigned long i = 0;
    std::string tmp;

    while (!isspace(s[i]) && i < s.length())
    {
        if (!std::isupper(s[i]))
            return error(METHOD_LOWERCASE , 1, req);
        tmp.push_back(s[i]);
        i++;
    }
    req->set_method(tmp);
    tmp.clear();
    i++;
    while (!isspace(s[i]) && i < s.length())
    {
        tmp.push_back(s[i]);
        i++;
    }
    req->set_url(tmp);
    tmp.clear();
    i++;
    while (!isspace(s[i]) && i < s.length())
    {
        tmp.push_back(s[i]);
        i++;
    }
    req->set_version(tmp);
    if (check_cgi(req, cgi))
       return error(BAD_CGI_VALUES, 1, req);
    return 0;
}

int catchvalues(const std::string s, std::map<std::string, std::string> &mp, Request *req)
{
    std::string name;
    std::string value;
    unsigned long i = 0;

    std::map<std::string, std::string>::iterator it = mp.begin();
    std::map<std::string, std::string>::iterator ite = mp.end();
    while (s[i] != ':' && i < s.length())
    {
        name.push_back(s[i]);
        i++;
    }
    while (it != ite) /* À TESTER LA REDEFINITION D'UN HEADER" */
    {
        if (!it->first.compare(name))
            return error(DEFINED_TWICE, 1, req);
        it++;
    }
    if (s[i] == ':' && i < s.length())
        i++;
    while (isspace(s[i]) && i < s.length())
        i++;
    while (s[i] != ';' && i < s.length())
    {
        if (isspace(s[i]))
            i++;
        else
        { 
            value.push_back(s[i]);
            i++;
        }
    }
    mp.insert(std::pair<std::string, std::string>(name, value));
    name.clear();
    value.clear();
    return 0;
}

void check_errors(Request *req)
{
    std::map<std::string, std::string>::iterator it;

    //A client MUST include a Host header field in all HTTP/1.1 request messages ->RFC: 14.23 Host
    if ((it = req->get_fields().find("Host")) == req->get_fields().end())
    {
        error(METHOD_HOST_MISSING, 1, req);
        return;
    }
}

void parsing(std::string file, Request *request)
{

        std::map<std::string, std::string> values;
        std::string cgi;
        std::string body;
        std::string line;

        int i = 0;
        while (file[i] && file[i] != '\n')
            line.push_back(file[i++]);
        line.push_back(file[i++]);
        if (!check_format_rqline(line, request))
        {
            line.erase(line.size() - 1);
            if (!catch_request_line(line, request, cgi))
            {
                line.clear();
                while (1)
                {
                    while (file[i] && file[i] != '\n')
                        line.push_back(file[i++]);
                    line.push_back(file[i++]);
                    if ((line[0] == '\r' && line[1] == '\n' ) || line[0] == '\n')
                        break;
                    if (!check_format_rqfield(line, request))
                    {
                        line.erase(line.size() - 1);
                        if (catchvalues(line, values, request) != 0)
                        {
                            parsingClear(values, body, line);
                            return;
                        }
                        line.clear();
                    }
                    else
                    {
                        parsingClear(values, body, line);
                        return;
                    }
                }
                std::string::iterator it = file.begin() + i;
                std::string::iterator ite = file.end();
                if (it != ite)
                {   
                    while (file[i])
                        body.push_back(file[i++]);
                }
            }
            else
            {
                parsingClear(values, body, line);
                error(CGI_CONTENT_TYPE, 1, request);
                return;
            }
        }
        else
        {
            parsingClear(values, body, line);
            return;
        }
        if (!cgi.empty())
        {
            std::map<std::string ,std::string>::iterator it = values.find("Content-Type");
            std::vector<std::string> content_type = request->get_contentTypeArray();
            std::vector<std::string>::iterator it_c = content_type.begin();
            std::vector<std::string>::iterator it_ce = content_type.end();

            while (it_c != it_ce )
            {
                if (!it->second.compare(*it_c))
                    break;
                it_c++;
            }
            if (it == values.end() || it_c == it_ce )
                request->set_contentType("text/html");
            else
                request->set_contentType(*it_c);
        }
        request->set_fields(values);
        request->set_cgi(cgi);
        request->set_body(body);
        //print_map(request->get_fields(), request->get_body());
        parsingClear(values, body, line);
        return;
}

Request req_parsing(std::string av)
{
    Request request;
    parsing(av, &request);
    return request;
}

/*
int main(int ac, char **av)
{
    Request request;
    std::vector<std::string> vec = request.get_contentTypeArray();

    std::ifstream input_file(av[1]);
    std::string file = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    if (ac < 2)
        return error(EMPTY, 0, &request);
    parsing(file, &request);
    printCGI(request.get_cgi());
    print_map(request.get_fields(), request.get_body());
    //check if there's an CLRF at the end of each lines and if there's empty line before the body
    return 0;
}*/