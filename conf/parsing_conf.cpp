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
                cpy.push_back(s1[i]);
                i++;
            }
            v.push_back(cpy);
            cpy.clear();
            i++;
        }
    }
    return v;
}

void check_server_block(std::vector<std::vector<std::string> > v, s_conf conf)
{
    std::vector<std::vector<std::string> >::iterator it = v.begin();
    std::vector<std::vector<std::string> >::iterator ite = v.end();
    std::vector<std::string>::iterator it_s, ite_s;

    while (it != ite)
    {
        it_s = it->begin();
        ite_s = it->end();
        while (it_s != ite_s)
        {
            if (it_s->compare("server") == 0 && conf.location_pos > 0)
            {
                error(SERVER_POSITION);
                return;
            }
            else
            {
                conf.nb_server++;
                std::cout << "server found" << std::endl;
                //check_position();
                return;
            }
            it_s++;
        }
        it++;
    }
}

void parsing(std::string file, s_conf conf)
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
        printlines(values);
        check_server_block(values, conf);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
}

void struct_init(s_conf conf)
{
    conf.nb_server = 0;
    conf.location_pos = 0;
    conf.listen.clear();
    conf.server_name.clear();
    conf.error_page.clear();
    conf.location.clear();
    conf.autoindex.clear();
    conf.index.clear();
    conf.root.clear();
}

int main(int ac, char **av)
{
    s_conf conf;
    if (ac < 2)
        return error(EMPTY);
    struct_init(conf);
    parsing(av[1], conf);
    return 0;
}