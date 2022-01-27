#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
{
    initValues();
    initErrorMap();
    initMethods();
}

bool HttpResponse::check_basic_error(Request *req)
{
    if (req->get_isErrorSyntax() == true)
    {
        req->set_url(ERROR_400_PATH);
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            _statusCode = 400;
            _reasonPhrase = _error[_statusCode];
            _contentLength = _content.size();
        }
        sourceFile.close();
        constructResponse();
        return false;
    }
    if (req->get_version().compare("HTTP/1.1") != 0)
    {
        req->set_url(ERROR_505_PATH);
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            _statusCode = 505;
            _reasonPhrase = _error[_statusCode];
            _contentLength = _content.size();
        }
        sourceFile.close();
        constructResponse();
        return false;
    }

    return true;
}

HttpResponse::HttpResponse(Request *req)
{
    initValues();
    initErrorMap();
    initMethods();
    int does_method_exist = 0;
    std::string method = req->get_method();

    if (check_basic_error(req) == false)
        return;
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
    _contentType = "text/html";
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
    _error.insert(std::pair<int, std::string>(411,"Length Required"));
    _error.insert(std::pair<int, std::string>(413,"Payload Too Large"));
    _error.insert(std::pair<int, std::string>(501,"Not Implemented")); //done
    _error.insert(std::pair<int, std::string>(505," HTTP Version Not Supported")); //done
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

void HttpResponse::requestParsingError(int code)
{
    _statusCode = 501;
    _reasonPhrase = _error[_statusCode];
    _contentType = "text/html";
    constructResponse();
}




void HttpResponse::handle_get_method(Request *req)  //add ParserConf here
{
    if (req->get_url() == "www/")
        req->set_url(HOME_PAGE_PATH);

    std::map<std::string, std::string> cgi = req->get_cgi();
    if (cgi.empty())
    {
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
    }
    else
    {
        //call to cgi here
    }
    constructResponse();
}





void HttpResponse::handle_post_method(Request *req)
{
    constructResponse();
}





void HttpResponse::handle_delete_method(Request *req)
{
    std::ifstream fileToDelete(req->get_url(), std::ifstream::in);

    if (fileToDelete.good())
    {
        if (!remove(req->get_url().c_str()))
        {
            req->set_url(FILE_DELETED);
            std::ifstream sourceFile(req->get_url(), std::ifstream::in);
            if (sourceFile.good())
            {
                std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
                _content = ans;
                _statusCode = 200;
                _reasonPhrase = _error[_statusCode];
                _contentLength = _content.size();
            }
            sourceFile.close();
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
            sourceFile.close();
        }
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
            sourceFile.close();
    }
    fileToDelete.close();
    constructResponse();
}

void HttpResponse::redirection(Request *req)
{

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
