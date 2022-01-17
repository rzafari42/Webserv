#include "HttpResponse.hpp"

HttpResponse::HttpResponse(Request *req)
{
    int does_method_exist = 0;
    std::string method = req->get_method();
    does_method_exist = check_method_existence(method);

    if (does_method_exist == 0)
    {
        if (!method.compare("GET"))
            handle_get_method(req);
        else if (!method.compare("POST"))
            handle_post_method(req);
        else
            handle_delete_method(req);
    }
    else if (does_method_exist == 1)
    {
        _httpVersion = "HTTP1.1";
        _statusCode = 501;
        _reasonPhrase = "Not Implemented";
        constructResponse();
    }
    else
    {
        _httpVersion = "HTTP1.1";
        _statusCode = 405;
        _reasonPhrase = "Method Not Allowed";
        constructResponse();
    }

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

    */
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

void HttpResponse::set_http_version(std::string version)
{
    _httpVersion = version;
}

void HttpResponse::set_status_code(int code)
{
    _statusCode = code;
}

void HttpResponse::set_reasonPhrase(std::string phrase)
{
    _reasonPhrase = phrase;
}

void HttpResponse::set_contentLength(int length)
{
    _contentLength = length;
}

void HttpResponse::set_content(std::string content)
{
    _content = content;
}

std::string HttpResponse::get_http_version()
{
    return _httpVersion;
}

int HttpResponse::get_status_code()
{
   return _statusCode;
}

std::string HttpResponse::get_reasonPhrase()
{
    return _reasonPhrase;
}

int HttpResponse::get_contentLength()
{
   return _contentLength;
}

std::string HttpResponse::get_content()
{
    return _content;
}

std::string HttpResponse::getResponse()
{
    return _response;
}

void HttpResponse::handle_get_method(Request *req)
{
    std::cout << "request: " << req->get_url() << "\n\n" << std::endl;
    if (req->get_url() == "/")
    {
        req->get_url() = "../www/index.html";
        std::cout << "request new url: " << req->get_url() << "\n\n" << std::endl;
    }
    std::ifstream sourceFile(req->get_url(), std::ifstream::in);

    if (sourceFile.good())
    {
        std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
        _content = ans;
        _httpVersion = "HTTP1.1";
        _statusCode = 200;
        _reasonPhrase = "OK";
        _contentLength = _content.size();
    }
    else
    {
        std::cout << "404 NOT FOUND" << std::endl;
        std::ifstream sourceFile("../www/error404.html", std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            _httpVersion = "HTTP1.1";
            _statusCode = 404;
            _reasonPhrase = "Not Found";
            _contentLength = _content.size();
        }
        else
            std::cout << "error while searching for the right file" << std::endl;
    }
    sourceFile.close();
    constructResponse();
}

void HttpResponse::handle_post_method(Request *req)
{
    constructResponse();
}

void HttpResponse::handle_delete_method(Request *req)
{

    constructResponse();
}

void HttpResponse::constructResponse()
{
    //Current Date and Time calulation
    time_t rawtime;
    struct tm * timeinfo;
    char date[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (date,80,"%a, %d %h %Y %H:%M:%S GMT",timeinfo);

    std::ostringstream file;
    file << _httpVersion << _statusCode << _reasonPhrase << "\r\n";
    file << "Cache-Control: no-cache, private\r\n";
    file << "Content-type: text/html\r\n";
    file << "Content-Length: " << _contentLength << "\r\n";
    file << "Content-Language: fr" << "\r\n";
    file << "date: " << date << "\r\n";
    file << "\r\n";
    file << _content;

    _response = file.str();
}