#ifndef PARSER_CONF_HPP
# define PARSER_CONF_HPP

# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define SERVER_POSITION "Error: Server block not declared at top"
# define LISTEN_EMPTY "Error: In Server: 'listen' directive exists but has no value"
# define ROOT_EMPTY "Error: In Server: 'root' directive exists but has no value"
# define INDEX_EMPTY "Error: In Server: 'index' directive exists but has no value"
# define ERROR_PAGE_EMPTY "Error: In Server: 'error_page' directive exists but has no value"
# define ERROR_PAGE_PATH_MISSING "Error: In Server: 'error_page' directive exists but path is missing"
# define SERVER_NAME_EMPTY "Error: In Server: 'server_name' directive exists but has no value"
# define CLIENT_MAX_BODY_SIZE_EMPTY "Error: In Server: 'client_max_body_size' directive exists but has no value"
# define AUTOINDEX_EMPTY "Error: In Server: 'autoindex' directive exists but has no value"
# define LOCATION_ROOT_EMPTY "Error: In Location: 'root' directive exists but has no value"
# define LOCATION_INDEX_EMPTY "Error: In Location: 'index' directive exists but has no value"
# define LOCATION_AUTOINDEX_EMPTY "Error: In Location: 'autoindex' directive exists but has no value"
# define LOCATION_RETURN_EMPTY "Error: In Location: 'return' directive exists but has no value"
# define LOCATION_RETURN_MISSING_PATH "Error: In Location: 'return' directive exists but path is missing"
# define LOCATION_CGI_EMPTY "Error: In Location: 'cgi' directive exists but has no value"
# define LOCATION_CGI_MISSING_PATH "Error: In Location: 'cgi' directive exists but path is missing"
# define LOCATION_METHODS_EMPTY "Error: In Location: 'methods' directive exists but has no value"
# define UNCLOSED_BRACKET "Error: '}' missing"
# define MISSING_SEMICOLON "Error: ';' missing"
# include <iostream>
# include <fstream>
# include <vector>
# include "ServerInfo.hpp"
# include "Location.hpp"

class ParserConf
{
private:

public:
    // constructor/ destructor
    ParserConf( void );
    ~ParserConf();

    void parse(std::string file, std::vector<ServerInfo> *serv_info);
    class ParsingConfigFileException : public std::exception {
        private:
            const char *_message;
            ParsingConfigFileException( void );

        public:
            ParsingConfigFileException(const char * message) : _message(message) {}
            virtual const char * what() const throw() { return _message; }
    };
};

#endif
