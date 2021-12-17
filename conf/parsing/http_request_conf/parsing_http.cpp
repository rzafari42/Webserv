#include "parsing_http.hpp"
#include "utils.hpp"

int check_format_rqline(std::string s)
{
    int i = 0;
    int nb_space = 0;
    int nb_arg = 0;

    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
            i++;
        nb_arg += 1;
        if (i < s.length())
            nb_space += 1;
        i++;
    }
    if (nb_space == 2 && nb_arg == 3)
        return 0;
    return error(REQUEST_LINE_FORMAT);
}

int check_format_rqfield(std::string s)
{
    int i = 0;
    int semi_colon = 0;
    int nb_arg = 0;
    
    while (i < s.length())
    {
        while (!isspace(s[i]) && i < s.length())
        {
            if (s[i] == ':')
            {
                semi_colon += 1;
                if (!isspace(s[ i + 1]))
                    return error(REQUEST_FIELD_FORMAT_SPACE);
                break;
            }
            i++;
        }
        if (s[i] != ':')
            nb_arg += 1;
        i++;
    }
    if (semi_colon == 1 && nb_arg >= 2)
        return 1;
    return error(REQUEST_FIELD_FORMAT);
}

int catch_request_line(const std::string s, s_request *req) //Format: Method Request-URI HTTP-Version CRLF
{
    int i = 0;
    std::string tmp;

    while (!isspace(s[i]))
    {
        if (!std::isupper(s[i]))
            return(error(METHOD_LOWERCASE));
        tmp.push_back(s[i]);
        i++;
    }
    req->req_line._method = tmp;
    tmp.clear();
    i++;
    while (!isspace(s[i]))
    {
        tmp.push_back(s[i]);
        i++;
    }
    req->req_line._url = tmp;
    tmp.clear();
    i++;
    while (i < s.length())
    {
        tmp.push_back(s[i]);
        i++;
    }
    req->req_line._version = tmp;
    return 0;
}

void catchvalues(const std::string s, std::map<std::string, std::string> &mp)
{
    std::string name;
    std::string value;
    int i = 0;

    while (s[i] != ':' && i < s.length())
    {
        name.push_back(s[i]);
        i++;
    }
    if (s[i] == ':' && i < s.length())
        i++;
    while (i < s.length())
    {
        value.push_back(s[i]);
        i++;
    }
    mp.insert(std::pair<std::string, std::string>(name, value));
    name.clear();
    value.clear();
}

void print_map(std::map<std::string, std::string> mymap)
{
    std::map<std::string,std::string>::iterator it;

    std::cout << "Map contains:\n";
    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << ": " << it->second << '\n';
}

void parsing(std::string file, s_request *request)
{
    std::ifstream flux(file);

    if (flux)
    {
        std::map<std::string, std::string> values;
        std::string line;

        getline(flux, line);
        if (!check_format_rqline(line))
        {
            if (!catch_request_line(line, request))
            {
                line.clear();
                while (getline(flux, line))
                {
                    if (check_format_rqfield(line))
                    {
                        catchvalues(line, values);
                        line.clear();
                    }
                    else
                        break;
                }
            }
            else
                return;
        }
        flux.close();
        request->fields = values;
        values.clear();
        print_map(request->fields);
        return;
    }
    else
        error(OPENING_FAILURE);
}

void check_errors(s_request *req)
{
    std::map<std::string, std::string>::iterator it;

    if ((it = req->fields.find("Host")) == req->fields.end())
    {
        error(METHOD_HOST_MISSING);
        return;
    }
}

int main(int ac, char **av)
{
    if (ac < 2)
        return error(EMPTY);
    s_request request;
    struct_init(&request);
    parsing(av[1], &request);
    check_errors(&request);
    //check if there's an CLRF at the end of each lines and if there's empty line before the body
    return 0;
}