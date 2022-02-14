/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:51:23 by simbarre          #+#    #+#             */
/*   Updated: 2022/02/07 22:22:23 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ParserConf.hpp"

ParserConf::ParserConf( void ) {}
ParserConf::~ParserConf() {}

static int error(std::string str) {
    std::cout << str << std::endl;
    return -1;
}

static std::vector<std::string> catchvalues(const std::string s)
{
    std::vector<std::string> v;
    std::string cpy;
    unsigned long i = 0;

    if (s.empty() == false)
    {
        while (i < s.length())
        {
            while (isspace(s[i]) && i < s.length())
                i++;
            while (!isspace(s[i]) && i < s.length())
            {
                if (s[i] == ';')
                    break ;
                cpy.push_back(s[i]);
                i++;
            }
            v.push_back(cpy);
            if (s[i] == ';')
            v.push_back(";");
            cpy.clear();
            i++;
        }
    }
    return v;
}

static int find_server_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite)
{
    while (it != ite)
    {
        if (!it->compare("server") && (++it) != ite && !it->compare("{"))
        {
            return 1;
        }
        it++;
    }
    return 0;
}


static void put_listen(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (it != ite)
        serv_info.set_listen(std::atoi((*it).c_str()));
    else
        throw ParserConf::ParsingConfigFileException(LISTEN_EMPTY);
}

static void put_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (it != ite)
        serv_info.set_root(*it);
    else
        throw ParserConf::ParsingConfigFileException(ROOT_EMPTY);

}

static void put_error_page(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (it != ite)
        serv_info.add_error_code(std::atoi((*it).c_str()));
    else
        throw ParserConf::ParsingConfigFileException(ERROR_PAGE_EMPTY);
    it++;
    if (it != ite)
        serv_info.add_error_path(*it);
    else
        throw ParserConf::ParsingConfigFileException(ERROR_PAGE_PATH_MISSING);
}

static void put_server_name(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
        if (it != ite)
            serv_info.set_server_name(*it);
        else
            throw ParserConf::ParsingConfigFileException(SERVER_NAME_EMPTY);
}

static void put_client_max_body_size(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
    if (it != ite)
        serv_info.set_client_max_body_size(std::atoi((*it).c_str()));
    else
        throw ParserConf::ParsingConfigFileException(CLIENT_MAX_BODY_SIZE_EMPTY);
}

static int find_element_server_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (!it->compare("listen"))
        put_listen(++it, ite, serv_info);
    else if (!it->compare("root"))
        put_root(++it, ite, serv_info);
    else if (!it->compare("error_page"))
        put_error_page(++it, ite, serv_info);
    else if (!it->compare("server_name"))
        put_server_name(++it, ite, serv_info);
    else if (!it->compare("client_max_body_size"))
        put_client_max_body_size(++it, ite, serv_info);
    else if (!it->compare("location"))
        return 0;
    else
        return 1; // FAILURE
    if ((ite - 1)->compare(";"))
        throw ParserConf::ParsingConfigFileException(MISSING_SEMICOLON);
    return 0; // SUCCESS
}

static void put_location_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (it != ite)
        loc.set_root(*it);
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_ROOT_EMPTY);
}

static void put_location_index(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (it != ite)
        loc.set_index(*it);
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_INDEX_EMPTY);
}

static void put_location_autoindex(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (it != ite)
        loc.set_autoindex(*it);
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_AUTOINDEX_EMPTY);
}

static void put_location_return(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (it != ite)
        loc.set_return_code(std::atoi((*it).c_str()));
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_RETURN_EMPTY);
    it++;
    if (it != ite)
        loc.set_return_path(*it);
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_RETURN_MISSING_PATH);

}

static void put_location_cgi(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (it != ite)
        loc.set_cgi_extension(*it);
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_CGI_EMPTY);
    it++;
    if (it != ite)
    {
        if (it->at(0) == '/')            
            it->erase(it->begin());
        loc.set_cgi_path(*it);
    }
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_CGI_MISSING_PATH);
}

static void put_location_methods(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    std::vector<std::string> *methods = loc.get_ptr_methods();
    if (it != ite) {
        while (it != ite && it->compare(";")) {
            methods->push_back(*it);
            it++;
        }
    }
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_METHODS_EMPTY);
}

static void put_location_cgi_methods(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    std::vector<std::string> *cgi_methods = loc.get_ptr_cgi_methods();
    if (it != ite) {
        while (it != ite && it->compare(";")) {
            cgi_methods->push_back(*it);
            it++;
        }
    }
    else
        throw ParserConf::ParsingConfigFileException(LOCATION_CGI_METHODS_EMPTY);
}

static int find_element_location_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &loc) {
    if (!it->compare("root"))
        put_location_root(++it, ite, loc);
    else if (!it->compare("index"))
        put_location_index(++it, ite, loc);
    else if (!it->compare("autoindex"))
        put_location_autoindex(++it, ite, loc);
    else if (!it->compare("return"))
        put_location_return(++it, ite, loc);
    else if (!it->compare("cgi"))
        put_location_cgi(++it, ite, loc);
    else if (!it->compare("methods"))
        put_location_methods(++it, ite, loc);
    else if (!it->compare("cgi_methods"))
        put_location_cgi_methods(++it, ite, loc);
    else
        return 1; // FAILURE
    if ((ite - 1)->compare(";"))
        throw ParserConf::ParsingConfigFileException(MISSING_SEMICOLON);
    return 0;
}

static void fill_struct(std::vector<std::vector<std::string> > v, std::vector<ServerInfo> *serv_info) {
    std::vector<std::vector<std::string> >::iterator it = v.begin();
    std::vector<std::vector<std::string> >::iterator ite = v.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;

    ServerInfo  conf_tmp;
    Location    loc_tmp;

    int brackets = 0;

    while (it != ite) {
        it_s = it->begin();
        ite_s = it->end();

        if (find_server_block(it_s, ite_s)) {
            conf_tmp = ServerInfo();
            brackets++;
            it++;
            it_s = it->begin();
            ite_s = it->end();
            while (it != ite && it_s->compare("}")) {
                // ELEMENTS IN SERVER BLOCK
                if (find_element_server_block(it_s, ite_s, conf_tmp))
                    throw ParserConf::ParsingConfigFileException("Error: In Server: invalid keyword");
                if (!it_s->compare("location")) {
                    loc_tmp = Location();
                    if (it_s != ite_s && (++it_s)->compare("{"))
                    {
                        size_t i = 0;
                        std::string tmp;
                        while (i < it_s->length() && it_s->at(i) != '{')
                        {
                            tmp.push_back(it_s->at(i));
                            i++;
                        }
                        loc_tmp.set_uri(tmp);
                    }
                    else
                        throw ParserConf::ParsingConfigFileException("Error: In Location, 'URI' is missing");
                    brackets++;
                    it++;
                    it_s = it->begin();
                    ite_s = it->end();
                    while (it != ite && it_s->compare("}")) {
                        // ELEMENTS IN LOCATION BLOCK
                        if (find_element_location_block(it_s, ite_s, loc_tmp))
                            throw ParserConf::ParsingConfigFileException("Error: In Location: invalid keyword");
                        it++;
                        it_s = it->begin();
                        ite_s = it->end();
                    }
                    brackets--;
                    if (!loc_tmp.get_cgi_extension().empty())
                        if (loc_tmp.get_cgi_methods().empty())
                            throw ParserConf::ParsingConfigFileException("Error: CGI is defined but has no methods");
                    conf_tmp.add_location(loc_tmp);
                }   
                if (it != ite) {
                    it++;
                    it_s = it->begin();
                    ite_s = it->end();
                }
            }
            brackets--;
            serv_info->push_back(conf_tmp);
        }
        if (it != ite) {
            it++;
        }
    }
    if (brackets) {
        error(UNCLOSED_BRACKET);
        serv_info->clear();
    }
    return;
}

void ParserConf::parse(std::string file, std::vector<ServerInfo> *serv_info) {
    std::ifstream flux(file.c_str());

    if (flux.good() == 1)
    {
        std::vector<std::vector<std::string> > values;
        std::vector<std::string> tmp;
        std::string line;

        while(getline(flux, line))
        {
            tmp = catchvalues(line);
            if (!tmp.empty()) {
                values.push_back(tmp);
                line.clear();
            }
        }
        fill_struct(values, serv_info);
        flux.close();
    }
    else
    {
        error(OPENING_FAILURE);
        exit(0);
    }
}