#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string source)
{
    std::ifstream sourceFile(source, std::ifstream::in);

    if (sourceFile.good())
    {
        std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
        content = ans;
        httpVersion = "HTTP1.1";
        statusCode = 200;
        reasonPhrase = "OK";
        contentLength = content.size();
    }
    else
    {
        std::cout << "404 NOT FOUND" << std::endl;
        source = "../Webpage/error.html";
        std::cout << "source: " << source << std::endl;
        std::ifstream sourceFile(source, std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            content = ans;
            httpVersion = "HTTP1.1";
            statusCode = 404;
            reasonPhrase = "Not Found";
            contentLength = content.size();
        }
        else
            std::cout << "error while searching for the right file" << std::endl;
    }
    sourceFile.close();

    std::ostringstream file;
    file << httpVersion << statusCode << reasonPhrase << "\r\n";
    file << "Cache-Control: no-cache, private\r\n";
    file << "Content-type: text/html\r\n";
    file << "Content-Length: " << contentLength << "\r\n";
    file << "\r\n";
    file << content;

    response = file.str();
}

HttpResponse::~HttpResponse(void)
{
}

std::string HttpResponse::getResponse()
{
    return response;
}