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
    int i = 0;
    int j;

    while (s1[i])
    {
        j = 0;
        cpy = "";
        while (s1[i] != ' ' && s1[i] != '\0')
        {
            cpy[j] = s1[i];
            //std::cout << cpy[j] << std::endl;
            i++;
            j++;
        }
        //cpy[++j] = '\0';
        std::cout << cpy << std::endl;
        std::cout << std::endl;
        v.push_back(cpy);
        i++;
    }
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

        while(getline(flux, line))
        {
            catchvalues(line);
            //values[i] = catchvalues(line);
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