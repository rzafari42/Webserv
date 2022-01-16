#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string method, std::string source)
{
    int does_method_exist = 0;
    does_method_exist = check_method_existence(method);

    if (does_method_exist == 0)
    {
        if (!method.compare("GET"))
            get_method();
        else if (!method.compare("POST"))
            post_method();
        else
            delete_method();
    }
    else if (does_method_exist == 1)
        return_error(501);
    else
        return_error(405);


    //METHOD GET
    /*std::ifstream sourceFile(source, std::ifstream::in);

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
        source = "www/error404.html";
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

    //Current Date and Time calulation
    time_t rawtime;
    struct tm * timeinfo;
    char date[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (date,80,"%a, %d %h %Y %H:%M:%S GMT",timeinfo);

    std::ostringstream file;
    file << httpVersion << statusCode << reasonPhrase << "\r\n";
    file << "Cache-Control: no-cache, private\r\n";
    file << "Content-type: text/html\r\n";
    file << "Content-Length: " << contentLength << "\r\n";
    file << "Content-Language: fr" << "\r\n";
    file << "date: " << date << "\r\n";
    file << "\r\n";
    file << content;

    response = file.str();*/
}

int  HttpResponse::check_method_existence(std::string method)
{
    if (!method.compare("GET") || !method.compare("POST") || !method.compare("DELETE"))
        return 0;
    else if (!method.compare("HEAD") || !method.compare("PUT") || !method.compare("CONNECT") || !method.compare("OPTIONS") || !method.compare("TRACE") || !method.compare("PATCH"))
        return 1;
    return -1;
}

HttpResponse::~HttpResponse(void)
{
}

std::string HttpResponse::getResponse()
{
    return response;
}