#include <iostream>
#include <fstream>
#include <vector>
#define EMPTY "Error: Not enough arguments"
#define OPENING_FAILURE "Error: File is not accessible in reading mode"

int error(std::string code)
{
    std::cout << code << std::endl;
    return -1;
}

void printlines(std::vector<std::vector<std::string> > s)
{
    int j;

    for (int i = 0; i < s.size(); i++)
    {
        j = 0;
        for (; j < s[i].size(); j++)
        {
            std::cout << s[i][j];
            if (j < s[i].size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}