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
        std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
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
        std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
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

HttpResponse::HttpResponse(Request *req, ServerInfo *conf)
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
            handle_get_method(req, conf);
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
    _redirectLoop = false;
}

void HttpResponse::initErrorMap()
{
    _error.insert(std::pair<int, std::string>(100,"Continue"));
    _error.insert(std::pair<int, std::string>(200,"OK")); //done
    _error.insert(std::pair<int, std::string>(201,"Created")); //for post method
    _error.insert(std::pair<int, std::string>(204,"No Content")); //for post method
    _error.insert(std::pair<int, std::string>(301,"Moved Permanently"));
    _error.insert(std::pair<int, std::string>(310,"Too many Redirects")); //done
    _error.insert(std::pair<int, std::string>(400,"Bad Request"));
    _error.insert(std::pair<int, std::string>(404,"Not Found")); //done
    _error.insert(std::pair<int, std::string>(405,"Method Not Allowed")); //done
    _error.insert(std::pair<int, std::string>(411,"Length Required"));
    _error.insert(std::pair<int, std::string>(413,"Payload Too Large"));
    _error.insert(std::pair<int, std::string>(501,"Not Implemented")); //done
    _error.insert(std::pair<int, std::string>(505,"HTTP Version Not Supported")); //done

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
    (void)code;                                 //just to fix compil error
    _statusCode = 501;
    _reasonPhrase = _error[_statusCode];
    _contentType = "text/html";
    constructResponse();
}

bool HttpResponse::CountLocRedirect(std::map<std::string, int> *mp, std::string uri)
{
    std::map<std::string ,int >::iterator it = mp->find(uri);
    if (it != mp->end())
    {
        it->second = it->second + 1;
        if (it->second == 2)    
            return true;
    }
    return false;
}

int HttpResponse::check_redirection(Request *req, ServerInfo *conf)
{
    //check if the url is present in one of the location bloc URI
    std::vector<Location> loc = conf->get_locations();
    std::vector<Location>::iterator it = loc.begin();
    std::vector<Location>::iterator ite = loc.end();

    while (it != ite)
    {
        std::string tmp_url = req->get_url().erase(0, 3);
        if (!it->get_uri().compare(tmp_url))
        {
            if (it->get_return_code() != 0)
            {
                req->set_url(it->get_return_path());
                if (!it->get_uri().compare(req->get_url().erase(0, 3)))
                {
                    set_redirectLoop();
                    return -1;
                }
                _statusCode = 301;
                return 0;
            }
            //checkIfRoot ...
        }
        it++;
    }
    return 1;
}

void HttpResponse::handle_get_method(Request *req, ServerInfo *conf)  //add ParserConf here
{
    std::vector<Location> loc = conf->get_locations();
    std::map<std::string, int> loc_count;
    std::vector<Location>::iterator it = loc.begin();
    std::vector<Location>::iterator ite = loc.end();

    while (it != ite)
    {
        loc_count.insert(std::pair<std::string, int>(it->get_uri(), 0));
        it++;
    }
    while (!check_redirection(req, conf))
    {
        if (CountLocRedirect(&loc_count, req->get_url().erase(0, 3)) == true)
        {
            set_redirectLoop();
            break;
        }
    }
    if (req->get_url() == "www/")
        req->set_url(HOME_PAGE_PATH);
    if (get_redirectLoop() == true)
    {
        req->set_url(ERROR_310_PATH);
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            _statusCode = 310;
            _reasonPhrase = _error[_statusCode];
            _contentLength = _content.size();
        }
        constructResponse();
    }
    std::map<std::string, std::string> cgi = req->get_cgi();
    if (cgi.empty())
    {
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);

        DIR *d;
        char* dir = new char[req->get_url().length() + 1];
        strcpy(dir, req->get_url().c_str());
        d = opendir(dir);
        if (d || !sourceFile.good())
        {
            req->set_url(ERROR_404_PATH);
            std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
            if (sourceFile.good())
            {
                std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
                _content = ans;
                _statusCode = 404;
                _reasonPhrase = _error[_statusCode];
                _contentLength = _content.size();
            }
        }
        constructResponse();
    }
    std::map<std::string, std::string> cgi = req->get_cgi();
    if (cgi.empty())
    {
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);

        DIR *d;
        char* dir = new char[req->get_url().length() + 1];
        strcpy(dir, req->get_url().c_str());
        d = opendir(dir);
        if (d || !sourceFile.good())
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
        else
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            _content = ans;
            if (_statusCode == 0)
                _statusCode = 200;
            _reasonPhrase = _error[_statusCode];
            _contentLength = _content.size();
            if (!req->get_url().compare(req->get_url().size() - 3, 3, "css"))
                _contentType = "text/css";
            else
                _contentType = "text/html";
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
    (void)req;
    constructResponse();
}


void HttpResponse::handle_delete_method(Request *req)
{
    std::ifstream fileToDelete(req->get_url().c_str(), std::ifstream::in);

    if (fileToDelete.good())
    {
        if (!remove(req->get_url().c_str()))
        {
            req->set_url(FILE_DELETED);
            std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
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
            std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
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
            std::ifstream sourceFile(req->get_url().c_str(), std::ifstream::in);
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
    (void)req;
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
