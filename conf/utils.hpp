#include <iostream>
#include <fstream>
#include <vector>
#define EMPTY "Error: Not enough arguments"
#define OPENING_FAILURE "Error: File is not accessible in reading mode"
#define SERVER_POSITION "Error: Server block not declared at top"
#define LISTEN_EMPTY "Error: 'listen' directive exists but has no value"
#define ROOT_EMPTY "Error: 'root' directive exists but has no value"
#define INDEX_EMPTY "Error: 'root' directive exists but has no value"
#define ERROR_PAGE_EMPTY "Error: 'error_page' directive exists but has no value"
#define SERVER_NAME_EMPTY "Error: 'server_name' directive exists but has no value"

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

void printlines(std::vector<std::vector<std::string> > s)
{
    int j;
    std::vector<std::vector<std::string> >::iterator it = s.begin();
    std::vector<std::vector<std::string> >::iterator ite = s.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;

    while (it != ite)
    {
        it_s = it->begin();
        ite_s = it->end();
        while(it_s != ite_s)
        {
            std::cout << *it_s;
            it_s++;
            if (it_s != ite_s)  
                std::cout << " ";
        }
        std::cout << std::endl;
        it++;
    }
}
