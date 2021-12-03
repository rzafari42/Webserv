#include "parsing_conf.hpp"

std::vector<std::string> catchvalues(const std::string s1)
{
    std::vector<std::string> v;
    std::string cpy;
    size_t i = 0;

    if (s1.empty() == false)
    {
        while (i < s1.length())
        {
            while (isspace(s1[i]))
                i++;
            while (!isspace(s1[i]) && i < s1.length())
            {
                if (s1[i] == '#')
                {
                    v.push_back("\0");
                    return v;
                }
                cpy.push_back(s1[i]);
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
    while (it != ite)
    {
        if (!it->compare("location") && (++it)->compare("\0") && !it->compare("{"))
        {
            conf.nb_location += 1;
            return 1;
        }
        it++;
    }
    return 0;
}

int find_listen(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, s_server &conf)
{
    if (!it->compare("listen"))
    {
        it++;
        if (it->compare("\0"))
        {
            conf.listen = *it;
            //std::cout << "listen = " << conf.listen << std::endl;
        }
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
        {
            conf.root = *it;
            //std::cout << "root = " << conf.root << std::endl;
        }
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
        {
            conf.index = *it;
            //std::cout << "index = " << conf.index << std::endl;
        }
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

void fill_struct(std::vector<std::vector<std::string> > v, std::vector<s_server> *conf)
{
    std::vector<std::vector<std::string> >::iterator it = v.begin();
    std::vector<std::vector<std::string> >::iterator ite = v.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;


    s_server conf_tmp;
    while (it != ite)
    {
        it_s = it->begin();
        ite_s = it->end();
        struct_init(&conf_tmp);
        if (find_server_block(it_s, ite_s, conf_tmp))
        {
            it++;
            while (it != ite && it_s->compare("}") && it_s->compare("location"))
            {
                it_s = it->begin();
                ite_s = it->end();
                if (find_listen(it_s, ite_s, conf_tmp) ||
                find_root(it_s, ite_s, conf_tmp) ||
                find_index(it_s, ite_s, conf_tmp) ||
                find_error_page(it_s, ite_s, conf_tmp) ||
                find_server_name(it_s, ite_s, conf_tmp))
                {
                    conf->clear();
                    return;
                }
                it++;
            }
            if (!it_s->compare("location"))
            {
                conf_tmp.nb_location += 1;
                if (find_location_block(it_s, ite_s, conf_tmp))
                {
                    
                }
            }
            if (it == ite)
            {
                conf->push_back(conf_tmp);
                return;
            }
            conf->push_back(conf_tmp);
        }
        it++;
    }
    return;
}

void parsing(std::string file, std::vector<s_server> *conf)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::vector<std::vector<std::string> > values;
        std::string line;
        int i = 0;
        int j = 0;

        while(getline(flux, line))
        {
            values.push_back(catchvalues(line));
            line.clear();
        }
        //printlines(values);
        fill_struct(values, conf);
        print_conf_struct(*conf);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    std::vector<s_server> conf;
    parsing(av[1], &conf);
    return 0;
}