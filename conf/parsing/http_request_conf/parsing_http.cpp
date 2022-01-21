/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:19:15 by rzafari           #+#    #+#             */
/*   Updated: 2022/01/21 17:03:28 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_http.hpp"
#include "utils.hpp"
#include <fstream>

int check_format_rqline(std::string s, Request *req)
{
    int i = 0;
    int nb_space = 0;
    int nb_arg = 0;

    /*if (s.find("\r\n") == std::string::npos)
        return error(REQUEST_LINE_FORMAT_CRLF, 1);*/
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
    int i = 0;
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

int catch_request_line(const std::string s, Request *req) //Format: Method Request-URI HTTP-Version CRLF
{
    int i = 0;
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
    return 0;
}

void catchvalues(const std::string s, std::map<std::string, std::string> &mp)
{
    std::string name;
    std::string value;
    int i = 0;

    while (s[i] != ':' && i < s.length())
    {
        name.push_back(s[i]);
        i++;
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
    std::ifstream flux(file);

    if (flux)
    {
        std::map<std::string, std::string> values;
        std::vector<std::string> body;
        std::string line;

        char c;
        while (flux.get(c) && c != '\n')
            line.push_back(c);
        line.push_back(c);
        if (!check_format_rqline(line, request))
        {
            line.erase(line.size() - 2);
            if (!catch_request_line(line, request))
            {
                line.clear();
                while (1)
                {
                    while (flux.get(c) && c != '\n')
                        line.push_back(c);
                    line.push_back(c);
                    if (!line.compare("\r\n"))
                        break;
                    if (!check_format_rqfield(line, request))
                    {
                        line.erase(line.size() - 2);
                        catchvalues(line, values);
                        line.clear();
                    }
                    else
                    {
                        flux.close();
                        values.clear();
                        return;
                    }
                }
                if (flux.eof() == false)
                {
                    if (values.find("Content-Length") != values.end())
                    {
                        std::cout << "content_length" << std::endl;
                        int body_size = std::stoi(values["Content-Length"]);
                        while (getline(flux, line) && body_size > 0)
                        {
                            body.push_back(line);
                            line.clear();
                            body_size--;
                        }
                    }
                    else
                        request->set_content_length_missing();
                }
            }
            else
            {
                flux.close();
                values.clear();
                return;
            }
        }
        else
        {
            flux.close();
            values.clear();
            return;
        }
        flux.close();
        request->set_fields(values);
        request->set_body(body);
        values.clear();
        body.clear();
        //print_map(request->get_fields());
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
    if (ac < 2)
        return error(EMPTY);
    Request request;
    parsing(av[1], &request);
    print_map(request.get_fields(), request.get_body());
    //check if there's an CLRF at the end of each lines and if there's empty line before the body
    return 0;
}*/