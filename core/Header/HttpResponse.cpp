#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string source)
{
    std::ifstream sourceFile(source, std::ifstream::in);

    if (sourceFile.good())
    {
        std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
        content = ans;
        statusCode = 200;
        reasonPhrase = "OK";
        httpVersion = "HTTP1.1";
        contentLength = content.size();
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