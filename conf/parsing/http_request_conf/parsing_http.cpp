#include "parsing_http.hpp"
#include "utils.hpp"

void insertvalue(std::string line, Request *request)
{

}

void parsing(std::string file, Request *request)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::vector<std::vector<std::string> > values;
        std::string line;

        while (getline(flux, line))
        {
            values.push_back(line);
            line.clear();
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
    Request request;
    parsing(av[1], &request);
    return 0;
}