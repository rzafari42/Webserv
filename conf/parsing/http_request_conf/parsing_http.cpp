/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:19:15 by rzafari           #+#    #+#             */
/*   Updated: 2022/01/30 14:33:54 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Header/main_header.hpp"

int check_format_rqline(std::string s, Request *req)
{
    unsigned long i = 0;
    int nb_space = 0;
    int nb_arg = 0;

    if (s.find("\r") == std::string::npos)
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

    if (s.find("\r\n") == std::string::npos)
        return error(REQUEST_FIELD_FORMAT_CRLF, 1, req);
    s.erase(s.size() - 2);
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

int check_cgi(Request *req, std::map<std::string, std::string> &mp)
{
    std::string url = req->get_url();
    std::size_t pos = 0;
    std::string key;
    std::string value;

    pos = url.find(CGI_EXTENSION);
    if (pos != std::string::npos)
    {
        while (url[pos] != '?' && pos != url.size())
            pos++;
        if (pos == url.size())
            return -1;
        while (pos != url.size())
        {
            pos++;
            key.clear();
            value.clear();
            while (pos != url.size() && url.at(pos) != '=')
            {
                key.push_back(url[pos]);
                pos++;
            }
            pos++;
            while (pos < url.size() && url.at(pos) != '&') 
            {
                value.push_back(url[pos]);
                pos++;
            }
            mp.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    return 0;
}

int catch_request_line(const std::string s, Request *req, std::map<std::string, std::string> &mp) //Format: Method Request-URI HTTP-Version CRLF
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
    while (i < s.length())
    {
        tmp.push_back(s[i]);
        i++;
    }
    req->set_version(tmp);
    if (check_cgi(req, mp))
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
    while (i < s.length())
    {
        value.push_back(s[i]);
        i++;
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
    std::ifstream flux(file.c_str());

    if (flux)
    {
        std::map<std::string, std::string> values;
        std::map<std::string, std::string> cgi;
        std::vector<std::string> body;
        std::string line;

        char c;
        while (flux.get(c) && c != '\n')
            line.push_back(c);
        line.push_back(c);
        if (!check_format_rqline(line, request))
        {
            line.erase(line.size() - 2);
            if (!catch_request_line(line, request, cgi))
            {
                line.clear();
                while (1)
                {
                    while (flux.get(c) && c != '\n')
                        line.push_back(c);
                    line.push_back(c);
                    if ((line[0] == '\r' && line[1] == '\n' ) || line[0] == '\r')
                        break;
                    if (!check_format_rqfield(line, request))
                    {
                        line.erase(line.size() - 2);
                        if (catchvalues(line, values, request) != 0)
                        {
                            parsingClear(flux, values, body, line);
                            return;
                        }
                        line.clear();
                    }
                    else
                    {
                        parsingClear(flux, values, body, line);
                        return;
                    }
                }
                if (flux.eof())
                {
                    while (getline(flux, line))
                    {
                        body.push_back(line);
                        line.clear();
                    }
                }
            }
            else
            {
                parsingClear(flux, values, body, line);
                return;
            }
        }
        else
        {
            parsingClear(flux, values, body, line);
            return;
        }
        request->set_fields(values);
        request->set_cgi(cgi);
        request->set_body(body);
        //print_map(request->get_fields(), request->get_body());
        parsingClear(flux, values, body, line);
        return;
    }
    else
        error(OPENING_FAILURE, 0, request);
}

Request req_parsing(std::string av)
{
    Request request;
    parsing(av, &request);
    return request;
}

/*int main(int ac, char **av)
{
    Request request;
    if (ac < 2)
        return error(EMPTY, 0, &request);
    parsing(av[1], &request);
    printCGI(request.get_cgi());
    print_map(request.get_fields(), request.get_body());
    //check if there's an CLRF at the end of each lines and if there's empty line before the body
    return 0;
}*/
