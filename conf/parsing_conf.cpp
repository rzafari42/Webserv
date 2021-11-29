#include "iostream"
#include <fstream>
#include "parsing_conf.hpp"
#define EMPTY "Error: Not enough arguments"
#define OPENING_FAILURE "Error: File is not accessible in reading mode"

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

void parsing(std::ifstream &flux)
{
    std::string line;

    while(getline(flux, line))
    {
        std::cout << line[0] << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    std::ifstream  flux(av[1]);

    if (flux)
    {
        parsing(flux);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
    return 0;
}