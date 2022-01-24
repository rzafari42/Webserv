#include "ParserConf.hpp"
#include "ServerInfo.hpp"
#include "Location.hpp"

ParserConf::ParserConf( void ) {}
ParserConf::~ParserConf() {}

static int error(std::string str) {
    std::cout << str << std::endl;
    return -1;
}

static std::vector<std::string> catchvalues(const std::string s)
{
    std::vector<std::string> v;
    std::string cpy;
    int i = 0;

    if (s.empty() == false)
    {
        while (i < s.length())
        {
            while (isspace(s[i]) && i < s.length())
                i++;
            while (!isspace(s[i]) && i < s.length())
            {
                if (s[i] == '#')
                {
                    v.push_back("\0");
                    return v;
                }
                cpy.push_back(s[i]);
                i++;
            }
            v.push_back(cpy);
            cpy.clear();
            i++;
        }
    }
    return v;
}

static int find_server_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite)
{
    while (it != ite)
    {
        if (!it->compare("server") && (++it) != ite && !it->compare("{"))
        {
            //TODO
            return 1;
        }
        it++;
    }
    return 0;
}

//static int find_element();

//static int find_element_location_block();

static int find_location_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite)
{
    if (!it->compare("location"))
    {
        while (it != ite)
        {
            if (!it->compare("{"))
            {
                //TODO LATER
                return 1;
            }
            it++;
        }
    }
    return 0;
}

static void put_listen(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (it != ite)
        serv_info.set_listen(*it);
    else
        throw ParserConf::ParsingConfigFileException(LISTEN_EMPTY);
}

static void put_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (it != ite)
        serv_info.set_root(*it);
    else
        throw ParserConf::ParsingConfigFileException(ROOT_EMPTY);
    
}

static void put_index(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
    if (it != ite)
        serv_info.set_index(*it);
    else
        throw ParserConf::ParsingConfigFileException(INDEX_EMPTY);
}

static void put_error_page(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
    std::string tmp;
    if (it != ite)
    {
        tmp = *it;
        it++;
        while (it != ite)
        {
            if (it != ite)
                tmp += ' ';
            tmp += *it;
            it++;
        }
        serv_info.set_error_page(tmp);
    }
    else
        throw ParserConf::ParsingConfigFileException(ERROR_PAGE_EMPTY);
}

static void put_server_name(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
        if (it != ite)
            serv_info.set_server_name(*it);
        else
            throw ParserConf::ParsingConfigFileException(SERVER_NAME_EMPTY);
}
static void put_autoindex(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
        if (it != ite)
            serv_info.set_autoindex(*it);
        else
            throw ParserConf::ParsingConfigFileException(AUTOINDEX_EMPTY);
}

static void put_client_max_body_size(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info)
{
    if (it != ite)
        serv_info.set_client_max_body_size(std::atoi((*it).c_str()));
    else
        throw ParserConf::ParsingConfigFileException(CLIENT_MAX_BODY_SIZE_EMPTY);
}

static int find_element_server_block(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, ServerInfo &serv_info) {
    if (!it->compare("listen"))
        put_listen(++it, ite, serv_info);
    else if (!it->compare("root"))
        put_root(++it, ite, serv_info);
    else if (!it->compare("index"))
        put_index(++it, ite, serv_info);
    else if (!it->compare("autoindex"))
        put_autoindex(++it, ite, serv_info);
    else if (!it->compare("error_page"))
        put_error_page(++it, ite, serv_info);
    else if (!it->compare("client_max_body_size"))
        put_client_max_body_size(++it, ite, serv_info);
    else
        return 1; // FAILURE
    return 0; // SUCCESS
}

static int find_location_root(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    if (!it->compare("root"))
    {
        it++;
        if (it != ite)
        {
            conf.set_root(*it);
        }
        else
            return error(LOCATION_ROOT_EMPTY);
    }
    return 0;
}

static int find_location_index(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    if (!it->compare("index"))
    {
        it++;
        if (it != ite)
        {
            conf.set_index(*it);
        }
        else
            return error(LOCATION_INDEX_EMPTY);
    }
    return 0;
}

static int find_location_autoindex(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    if (!it->compare("autoindex"))
    {
        it++;
        if (it != ite)
        {
            conf.set_autoindex(*it);
        }
        else
            return error(LOCATION_AUTOINDEX_EMPTY);
    }
    return 0;
}

static int find_location_error_page(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    if (!it->compare("error_page"))
    {
        it++;
        if (it != ite)
        {
            conf.set_error_page(*it);
        }
        else
            return error(LOCATION_ERROR_PAGE_EMPTY);
    }
    return 0;
}

static int find_location_client_max_body_size(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    if (!it->compare("client_max_body_size"))
    {
        it++;
        if (it != ite)
        {
            std::string str = *it;
            conf.set_client_max_body_size(std::atoi(str.c_str()));
        }
        else
            return error(LOCATION_CLIENT_MAX_BODY_SIZE_EMPTY);
    }
    return 0;
}

static int find_location_methods(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite, Location &conf)
{
    std::vector<std::string> *methods = conf.get_ptr_methods();
    if (!it->compare("methods"))
    {
        it++;
        if (it != ite)
        {
            while (it != ite)
            {
                methods->push_back(*it);
                it++;
            }
        }
        else
            return error(LOCATION_METHODS_EMPTY);
    }
    return 0;
}

static void fill_struct(std::vector<std::vector<std::string> > v, std::vector<ServerInfo> *serv_info)
{
    std::vector<std::vector<std::string> >::iterator it = v.begin();
    std::vector<std::vector<std::string> >::iterator ite = v.end();
    std::vector<std::string>::iterator it_s;
    std::vector<std::string>::iterator ite_s;

    ServerInfo  conf_tmp;
    Location    loc_tmp;

    int brackets = 0;

    while (it != ite) {
        it_s = it->begin();
        ite_s = it->end();

        if (find_server_block(it_s, ite_s)) {
            conf_tmp = ServerInfo();
            brackets++;
            it_s = it->begin();
            ite_s = it->end();
            while (it != ite && it_s->compare("}")) {
                // ELEMENTS IN SERVER BLOCK
                if (find_element_server_block) {
                    serv_info->clear();
                    return;
                }
                if (!it_s->compare("location")) {
                    loc_tmp = Location();
                    brackets++;
                    while (it != ite && it_s->compare("}")) {
                        // ELEMENTS IN LOCATION BLOCK
                        if (find_location_root(it_s, ite_s, loc_tmp) ||
                                find_location_index(it_s, ite_s, loc_tmp) ||
                                find_location_autoindex(it_s, ite_s, loc_tmp) ||
                                find_location_client_max_body_size(it_s, ite_s, loc_tmp) ||
                                find_location_error_page(it_s, ite_s, loc_tmp) ||
                                find_location_methods(it_s, ite_s, loc_tmp)) {
                            serv_info->clear();
                            return;
                        }
                        it++;
                        it_s = it->begin();
                        ite_s = it->end();  
                    }
                    brackets--;
                    conf_tmp.add_location(loc_tmp);
                }
                if (it != ite) {
                    it++;
                    it_s = it->begin();
                    ite_s = it->end();
                }
            }
            brackets--;
            serv_info->push_back(conf_tmp);
        }
        if (it != ite) {
            it++;
        }
    }
    if (brackets) {
        error(UNCLOSED_BRACKET);
        serv_info->clear();
    }
    return;
}



const char * ParserConf::ParsingConfigFileException::what(const char*) const throw() {
    return "ParsingFileException";
}

void ParserConf::parse(std::string file, std::vector<ServerInfo> *serv_info) {
    std::ifstream flux(file);

    if (flux)
    {
        std::vector<std::vector<std::string>> values;
        std::vector<std::string> tmp;
        std::string line;

        while(getline(flux, line))
        {
            tmp = catchvalues(line);
            if (!tmp.empty()) {
                values.push_back(tmp);
                line.clear();
            }
        }
        fill_struct(values, serv_info);
        flux.close();
    }
    else
        error(OPENING_FAILURE);
}
