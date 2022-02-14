#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main()
{
    std::string fileToParse =  getenv("BODY");
    std::string boundary;
    std::string filename;
    std::string content;
    std::size_t found = fileToParse.find("filename=\"");
    found += strlen("filename=\"") - 1;

    if (found == std::string::npos)
        return 1;

    while (fileToParse[++found] != '"')
        filename.push_back((fileToParse[found]));


    size_t i  = 0;

    found = fileToParse.find("\r\n\r\n");
    found += strlen("\r\n\r\n") - 1;

    if (found == std::string::npos)
        return 1;

    std::size_t found1 = fileToParse.find("-----------------------", found + 1);

    while (++found < found1)
        content.push_back((fileToParse[found]));

    std::ofstream myfile;
    myfile.open (filename);
    myfile << content;
    myfile.close();

}
