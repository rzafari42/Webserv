#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>      

struct File
{
    std::string fileName;
    std::string body;
};

void getFileName(std::string fileToParse, File *file)
{
    size_t pos = fileToParse.find("name");

    pos += 6;
    while (fileToParse[pos] != '\"')
    {
        file->fileName.push_back(fileToParse[pos]);
        pos++;
    }
}

int main()
{
    std::cout << getenv("BODY") << std::endl;


    std::string fileToParse =  getenv("BODY");

    File *file;
    std::string boundary;
    std::string line;
    std::ifstream flux(fileToParse.c_str());
    getline(flux, boundary);
    boundary.append("--");
    getline(flux, line);
    getFileName(line, file);
    getline(flux, line);
    while (getline(flux, line))
    {
        if (!line.compare(boundary))
            break;
        file->body.append(line);
    }
    std::ofstream myfile;
	myfile.open(file->fileName, std::ofstream::app);
	myfile << file->body;
	myfile.close();

}