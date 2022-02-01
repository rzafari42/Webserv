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

bool HttpResponse::check_redirection(Request *req, Location loc) {
    //check if the url is present in one of the location bloc URI
    if (loc.get_return_code() != 0 && !loc.get_return_path().empty()) {
        return true;
    }
    return false;
}

static Location *which_location(std::vector<Location> *loc, std::string url) {
    std::vector<Location>::iterator it = loc->begin();
    std::vector<Location>::iterator ite = loc->end();

    std::string tmp = url;

    while(tmp.compare("")) {
        it = loc->begin();
        while (it != ite) {
            if (!(tmp.compare(it->get_uri())))
                return &(*it);
            it++;
        }
        size_t found = tmp.rfind('/');
        if (found!=std::string::npos)
            tmp.replace(found, tmp.length() - found, "");
        else {
            // IF WE HERE WE F*CKED
        }
    }
    return NULL;
}

static bool ft_is_directory(std::string path){
    struct stat s;
    
    stat(path.c_str(), &s);
    if(s.st_mode & S_IFDIR)
        return true;
    return false;
}

void HttpResponse::handle_get_method(Request *req, ServerInfo *conf, size_t redirects)  //add ParserConf here
{
    std::cout << std::endl << req->get_url() << std::endl;
    std::vector<Location> locations = conf->get_locations();

    Location *loc = which_location(&locations, req->get_url());

    if (redirects > 20)
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
        return ;
    }

    if (loc) {
        if (check_redirection(req, *loc)) {
            std::string st = req->get_url();
            _statusCode = loc->get_return_code();
            st.replace(0, loc->get_uri().length(), loc->get_return_path());
            req->set_url(st);
            this->handle_get_method(req, conf, redirects + 1);
            return ;
        }
    }

    std::string path_tofile = req->get_url();
    if (loc)
        path_tofile = loc->get_root() + path_tofile;
    path_tofile = conf->get_root() + path_tofile;
    if (loc)
        if (ft_is_directory(path_tofile))
            path_tofile = path_tofile + loc->get_index();

    req->set_url(path_tofile);
    std::cout << std::endl << req->get_url() << std::endl;

    std::map<std::string, std::string> cgi = req->get_cgi();
    if (cgi.empty())
    {
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);

        DIR *d;
        char* dir = new char[req->get_url().length() + 1];
        std::strcpy(dir, req->get_url().c_str());
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
