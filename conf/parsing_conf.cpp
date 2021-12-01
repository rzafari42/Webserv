#include "iostream"
#include <fstream>
#include <vector>
#include "parsing_conf.hpp"
#define EMPTY "Error: Not enough arguments"
#define OPENING_FAILURE "Error: File is not accessible in reading mode"

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

std::vector<std::string> catchvalues(const std::string s1)
{
    std::vector<std::string> v;
    std::string cpy;
    size_t i = 0;

    //if (s1)
    //{
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
   // }
    return v;
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
        for (int i = 0; i < values.size(); i++)
        {
            j = 0;
            for (int j = 0; j < values[i].size(); j++)
            {
                std::cout << values[i][j];
                if (j < values[i].size() - 1)
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
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