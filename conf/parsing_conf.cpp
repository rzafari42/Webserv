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

std::vector<std::string > catchvalues(const std::string s1)
{
    /*std::string s2;
    size_t j = 0;

    for (size_t i = 0; i < s1.length(); i++)
    {
        if (s1[i] != ' ')
        {
            std::cout << s1[i];
            s2[j++] = s1[i];
        }
    }
    return s2; */
}

void parsing(std::string file)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::vector<std::vector<std::string> > values;
        std::string line;
        int i = 0;

        while(getline(flux, line))
        {
            std::vector<std::string > s = catchvalues(line);
            values[i].push_back(s);
            //std::cout << line << std::endl;
            i++;
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