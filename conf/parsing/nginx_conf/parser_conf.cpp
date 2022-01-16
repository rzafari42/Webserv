#include "utils.hpp"
#include "ServerInfo.hpp"
#include "Location.hpp"

std::vector<std::string> catchvalues(const std::string s)
{
    std::vector<std::string> v;
    std::string cpy;
    int i = 0;

    if (s.empty() == false)
    {
        while (i < s.length())
        {
            while (isspace(s[i]) && i < s.length())
                i++;
            while (!isspace(s[i]) && i < s.length())
            {
                if (s[i] == '#')
                {
                    v.push_back("\0");
                    return v;
                }
                cpy.push_back(s[i]);
                i++;
            }
            v.push_back(cpy);
            cpy.clear();
            i++;
        }
    }
    v.push_back("\0");
    return v;
}

int find_server_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    while (it != ite)
    {
        if (!it->compare("server") && (++it)->compare("\0") && !it->compare("{"))
        {
            conf.nb_server += 1;
            return 1;
        }
        it++;
    }
    return 0;
}

int find_location_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("location"))
    {
        while (it != ite)
        {
            if (!it->compare("{"))
            {
                conf.nb_location += 1;
                return 1;
            }
            it++;
        }
    }
    return 0;
}

int find_listen(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("listen"))
    {
        it++;
        if (it->compare("\0"))
            conf.listen = *it;
        else
            return error(LISTEN_EMPTY);
    }
    return 0;
}

int find_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("root"))
    {
        it++;
        if (it->compare("\0"))
            conf.root = *it;
        else
            return error(ROOT_EMPTY);
    }
    return 0;
}

int find_index(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("index"))
    {
        it++;
        if (it->compare("\0"))
            conf.index = *it;
        else
            return error(INDEX_EMPTY);
    }
    return 0;
}

int find_error_page(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("error_page"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.error_page = *it;
            it++;
            while (it != ite)
            {
                if (it->compare("\0"))
                    conf.error_page += ' ';
                conf.error_page += *it;
                it++;
            }
            //std::cout << "error_page = " << conf.error_page << std::endl;
        }
        else
            return error(ERROR_PAGE_EMPTY);
    }
    return 0;
}

int find_server_name(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("server_name"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.server_name = *it;
            //std::cout << "server_name = " << conf.server_name << std::endl;
        }
        else
            return error(SERVER_NAME_EMPTY);
    }
    return 0;
}

int find_autoindex(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("autoindex"))
    {
        it++;
        if (it->compare("\0"))
            conf.server_name = *it;
        else
            return error(AUTOINDEX_EMPTY);
    }
    return 0;
}

int find_client_max_body_size(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("client_max_body_size"))
    {
        it++;
        if (it->compare("\0"))
        {
            std::string str = *it;
            conf.client_max_body_size = std::atoi(str.c_str());
        }
        else
            return error(CLIENT_MAX_BODY_SIZE_EMPTY);
    }
    return 0;
}

int find_location_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &conf)
{
    std::vector<Location::Location> tmp = conf.get_locations()
    if (!it->compare("root"))
    {
        it++;
        if (it->compare("\0"))
        {
            tmp[tmp.end - 1].set_root(*it);
        }
        else
            return error(LOCATION_ROOT_EMPTY);
    }
    return 0;
}

int find_location_index(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("index"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.location.index = *it;
        }
        else
            return error(LOCATION_INDEX_EMPTY);
    }
    return 0;
}

int find_location_autoindex(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("autoindex"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.location.autoindex = *it;
        }
        else
            return error(LOCATION_AUTOINDEX_EMPTY);
    }
    return 0;
}

int find_location_error_page(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("error_page"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.location.error_page = *it;
        }
        else
            return error(LOCATION_ERROR_PAGE_EMPTY);
    }
    return 0;
}

int find_location_client_max_body_size(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("client_max_body_size"))
    {
        it++;
        if (it->compare("\0"))
        {
            std::string str = *it;
            conf.location.client_max_body_size = std::atoi(str.c_str());
        }
        else
            return error(LOCATION_CLIENT_MAX_BODY_SIZE_EMPTY);
    }
    return 0;
}

int find_location_methods(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("methods"))
    {
        it++;
        if (it->compare("\0"))
        {
            while (*it != "\0")
            {
                conf.location.methods.push_back(*it);
                it++;
            }
        }
        else
            return error(LOCATION_METHODS_EMPTY);
    }
    return 0;  
}

void fill_struct(std::vector<std::vector<std::string> > v, std::vector<ServerInfo> *serv_info)
{
    std::vector<std::vector<std::string> >::iterator it = v.begin();
    std::vector<std::vector<std::string> >::iterator ite = v.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;


    ServerInfo conf_tmp;
    while (it != ite)
    {
        it_s = it->begin();
        ite_s = it->end();
        struct_init(&conf_tmp);
        if (find_server_block(it_s, ite_s, conf_tmp))
        {
            it++;
            it_s = it->begin();
            ite_s = it->end();
            while (it != ite && it_s->compare("}") && it_s->compare("location"))
            {
                if (find_listen(it_s, ite_s, conf_tmp) ||
                find_root(it_s, ite_s, conf_tmp) ||
                find_index(it_s, ite_s, conf_tmp) ||
                find_error_page(it_s, ite_s, conf_tmp) ||
                find_server_name(it_s, ite_s, conf_tmp) ||
                find_client_max_body_size(it_s, ite_s, conf_tmp) ||
                find_autoindex(it_s, ite_s, conf_tmp))
                {
                    serv_info->clear();
                    return;
                }
                it++;
                it_s = it->begin();
                ite_s = it->end();
            }
            if (it == ite)
            {
                error(UNCLOSED_BRACKET);
                serv_info->clear();
                return;
            }
            else if (!it_s->compare("}"))
                conf_tmp.inc_closing_br();
            else if (!it_s->compare("location"))
            {
                if (find_location_block(it_s, ite_s, conf_tmp))
                {
                    it++;
                    it_s = it->begin();
                    ite_s = it->end();
                    while (it != ite && it_s->compare("}"))
                    {
                        if (find_location_root(it_s, ite_s, conf_tmp) || 
                        find_location_index(it_s, ite_s, conf_tmp) ||
                        find_location_autoindex(it_s, ite_s, conf_tmp) ||
                        find_location_client_max_body_size(it_s, ite_s, conf_tmp) ||
                        find_location_error_page(it_s, ite_s, conf_tmp) ||
                        find_location_methods(it_s, ite_s, conf_tmp))
                        {
                            serv_info->clear();
                            return;
                        }
                        it++;
                        it_s = it->begin();
                        ite_s = it->end();
                    }
                    if (it == ite)
                    {
                        error(UNCLOSED_BRACKET);
                        serv_info->clear();
                        return;   
                    }
                    else if (!it_s->compare("}"))
                        conf_tmp.inc_closing_br();
                }
            }
            it++;
            it_s = it->begin();
            ite_s = it->end();
            if (it != ite && !it_s->compare("}"))
                conf_tmp.inc_closing_br();
            if (conf_tmp.get_nb_closing_br() != conf_tmp.nb_server + conf_tmp.nb_location)
            {
                error(UNCLOSED_BRACKET);
                serv_info->clear();
                return;
            }
            else
                serv_info->push_back(conf_tmp);
            //print_location_methods_struct(conf_tmp.location.methods);
        }
        if (it != ite)
            it++;
    }
    return;
}

void parsing(std::string file, std::vector<ServerInfo> *serv_info)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::vector<std::vector<std::string> > values;
        std::string line;

        while(getline(flux, line))
        {
            values.push_back(catchvalues(line));
            line.clear();
        }
        fill_struct(values, serv_info);
        //printlines(values);
        print_conf_struct(*serv_info);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    std::vector<ServerInfo> serv_info;
    parsing(av[1], &serv_info);
    return 0;
}