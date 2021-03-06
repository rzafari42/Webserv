#ifndef MAIN_HEADER_HPP
# define MAIN_HEADER_HPP

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <cstring>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdbool.h>
# include <limits.h>
# include <iostream>
# include <fstream>
# include <map>
# include <vector>
# include <sstream>
# include <algorithm>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define HTTP_VERSION "HTTP/1.1"

# define ERROR_400_PATH "www/error400.html"
# define ERROR_403_PATH "www/error403.html"
# define ERROR_404_PATH "www/error404.html"
# define ERROR_405_PATH "www/error405.html"
# define ERROR_411_PATH "www/error411.html"
# define ERROR_500_PATH "www/error500.html"
# define ERROR_505_PATH "www/error505.html"
# define ERROR_310_PATH "www/error310.html"

# define FILE_DELETED "www/file_deleted.html"

# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define REQUEST_LINE_FORMAT "Error: Header Request-Line bad format."
# define REQUEST_LINE_FORMAT_CRLF "Error: Header Request-Line bad format. CRLF Missing !"
# define REQUEST_FIELD_FORMAT "Error: Header fields bad format."
# define REQUEST_FIELD_FORMAT_SPACE "Error: In Header fields. No space before field value."
# define REQUEST_FIELD_FORMAT_CRLF "Error: Header fields bad format. CRLF Missing !"
# define METHOD_LOWERCASE "Error: In Header Request-Line. Method is in lowercase."
# define CGI_CONTENT_TYPE "Error: In Request. CGI is defined but Content-Type header is missing or has bad syntax!"
# define METHOD_HOST_MISSING "400 Bad Request"
# define PROTOCOL_VERSION "HTTP/1.1"
# define DEFINED_TWICE "Error: Header Element Defined Twice"
# define BAD_CGI_VALUES "Error: CGI values are incorrect or missing"
# define CRLF "\r\n"
# define CR '\r'
# define LF '\n'

#endif
