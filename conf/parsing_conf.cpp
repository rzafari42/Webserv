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

void check_server_block(std::vector<std::vector<std::string> > v)
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
            if (it_s->compare("server") == 0)
            {
                check_position();
                return;
            }
            it_s++;
        }
        it++;
    }
}

void parsing(std::string file)
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
        check_server_block(values);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    parsing(av[1]);
    return 0;
}