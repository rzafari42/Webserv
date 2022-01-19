#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
{
    initValues();
    initErrorMap();
    initMethods();
}

HttpResponse::HttpResponse(Request *req)
{
    initValues();
    initErrorMap();
    initMethods();
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
    else
    {
        if (does_method_exist == 1)
            _statusCode = 501;
        else
            _statusCode = 405;
        _reasonPhrase = _error[_statusCode];
        constructResponse();
    }
}

void HttpResponse::initValues()
{
    _statusCode = 0;
    _reasonPhrase = "";
    _contentLength = 0; 
    _content = ""; 
    _contentType = "";
    _response = ""; 
}

void HttpResponse::initErrorMap()
{
    _error.insert(std::pair<int, std::string>(100,"Continue"));
    _error.insert(std::pair<int, std::string>(200,"OK")); //done
    _error.insert(std::pair<int, std::string>(201,"Created")); //for post method
    _error.insert(std::pair<int, std::string>(204,"No Content")); //for post method
    _error.insert(std::pair<int, std::string>(301,"Moved Permanently"));
    _error.insert(std::pair<int, std::string>(400,"Bad Request"));
    _error.insert(std::pair<int, std::string>(404,"Not Found")); //done
    _error.insert(std::pair<int, std::string>(405,"Method Not Allowed")); //done
    _error.insert(std::pair<int, std::string>(413,"Payload Too Large")); 
    _error.insert(std::pair<int, std::string>(501,"Not Implemented")); //done
}

void HttpResponse::initMethods()
{
    _implementedMethods.push_back("GET");
    _implementedMethods.push_back("POST");
    _implementedMethods.push_back("DELETE");

    _notImplementedMethods.push_back("HEAD");
    _notImplementedMethods.push_back("PUT");
    _notImplementedMethods.push_back("CONNECT");
    _notImplementedMethods.push_back("OPTIONS");
    _notImplementedMethods.push_back("TRACE");
    _notImplementedMethods.push_back("PATCH");
}

int  HttpResponse::check_method_existence(std::string method)
{
    std::vector<std::string>::iterator it;

    it = std::find(_implementedMethods.begin(), _implementedMethods.end(), method);
    if (it != _implementedMethods.end())
        return 0;
    else
    {
        it = std::find(_notImplementedMethods.begin(), _notImplementedMethods.end(), method);
        if (it == _notImplementedMethods.end())
            return 1;
    }
    return -1;
}

HttpResponse::~HttpResponse(void)
{
    _error.clear();
    _implementedMethods.clear();
    _notImplementedMethods.clear();
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
    return HTTP_VERSION;
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
    if (req->get_url() == "www/")
        req->set_url(HOME_PAGE_PATH);

    std::ifstream sourceFile(req->get_url(), std::ifstream::in);

    if (sourceFile.good())
    {
        std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
        _content = ans;
        _statusCode = 200;
        _reasonPhrase = _error[_statusCode];
        _contentLength = _content.size();
        if (!req->get_url().compare(req->get_url().size() - 3, 3, "css"))
            _contentType = "text/css";
        else
            _contentType = "text/html";
    }
    else
    {
        req->set_url(ERROR_404_PATH);
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            _statusCode = 404;
            _reasonPhrase = _error[_statusCode];
            _contentLength = _content.size();
        }
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
    file << HTTP_VERSION << " " << _statusCode << " " << _reasonPhrase << "\r\n";
    file << "Cache-Control: no-cache, private\r\n";
    file << "Content-type: " << _contentType << "\r\n";
    file << "Content-Length: " << _contentLength << "\r\n";
    file << "Content-Language: fr" << "\r\n";
    file << "date: " << date << "\r\n";
    file << "\r\n";
    file << _content;

    _response = file.str();
}