/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_http.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:19:15 by rzafari           #+#    #+#             */
/*   Updated: 2021/12/21 16:52:40 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_http.hpp"
#include "utils.hpp"

int check_format_rqline(std::string s)
{
    int i = 0;
    int nb_space = 0;
    int nb_arg = 0;

    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
            i++;
        nb_arg += 1;
        if (i < s.length() && s[i] != CR)
            nb_space += 1;
        i++;
    }
    if (s.find(std::string(1, CR)) == std::string::npos)// || s.find(std::string(1, '\n')) == std::string::npos)
        return error(REQUEST_LINE_FORMAT_CRLF);
    if (nb_space == 2 && nb_arg == 3)
        return 0;
    return error(REQUEST_LINE_FORMAT);
}

int check_format_rqfield(std::string s)
{
    int i = 0;
    int semi_colon = 0;
    int nb_arg = 0;
    
    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
        {
            if (s[i] == ':' && semi_colon == 0)
            {
                semi_colon += 1;
                if (!isspace(s[ i + 1]))
                    return error(REQUEST_FIELD_FORMAT_SPACE);
                break;
            }
            i++;
        }
        if (s[i] != ':')
            nb_arg += 1;
        i++;
    }
    if (s.find(std::string(1,CR)) == std::string::npos)
        return error(REQUEST_FIELD_FORMAT_CRLF);
    if (semi_colon == 1 && nb_arg >= 2)
        return 1;
    return error(REQUEST_FIELD_FORMAT);
}

int catch_request_line(const std::string s, Request *req) //Format: Method Request-URI HTTP-Version CRLF
{
    int i = 0;
    std::string tmp;

    while (!isspace(s[i]))
    {
        if (!std::isupper(s[i]))
            return(error(METHOD_LOWERCASE));
        tmp.push_back(s[i]);
        i++;
    }
    req->set_method(tmp);
    tmp.clear();
    i++;
    while (!isspace(s[i]))
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
        error(METHOD_HOST_MISSING);
        return;
    }
}

void parsing(std::string file, Request *request)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::map<std::string, std::string> values;
        std::string line;

        getline(flux, line);
        if (!check_format_rqline(line))
        {
            if (!catch_request_line(line, request))
            {
                line.clear();
                while (getline(flux, line))
                {
                    if (check_format_rqfield(line))
                    {
                        catchvalues(line, values);
                        line.clear();
                    }
                    else
                        break;
                }
            }
            else
                return;
        }
        else
        {
            flux.close();
            values.clear();
            return;
        }
        flux.close();
        request->set_fields(values);
        values.clear();
        //print_map(request->get_fields());
        return;
    }
    else
        error(OPENING_FAILURE);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    Request request;
    parsing(av[1], &request);
    //check if there's an CLRF at the end of each lines and if there's empty line before the body
    return 0;
}