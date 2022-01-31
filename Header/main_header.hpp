/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:13:24 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/31 21:14:02 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <string.h>
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

# define HTTP_VERSION "HTTP/1.1"

# define HOME_PAGE_PATH "/index.html"
# define ERROR_400_PATH "/error400.html"
# define ERROR_404_PATH "/error404.html"
# define ERROR_411_PATH "/error411.html"
# define ERROR_505_PATH "/error505.html"
# define ERROR_310_PATH "/error310.html"

# define FILE_DELETED "/file_deleted.html"

#include "../conf/parsing/http_request_conf/parsing_http.hpp"
#include "../conf/parsing/nginx_conf/Location.hpp"
#include "../conf/parsing/nginx_conf/ServerInfo.hpp"
#include "../conf/parsing/nginx_conf/ParserConf.hpp"
#include "HttpResponse.hpp"
#include "CGI_Handler.hpp"


# define EMPTY "Error: Not enough arguments"
# define OPENING_FAILURE "Error: File is not accessible in reading mode"
# define REQUEST_LINE_FORMAT "Error: Header Request-Line bad format."
# define REQUEST_LINE_FORMAT_CRLF "Error: Header Request-Line bad format. CRLF Missing !"
# define REQUEST_FIELD_FORMAT "Error: Header fields bad format."
# define REQUEST_FIELD_FORMAT_SPACE "Error: In Header fields. No space before field value."
# define REQUEST_FIELD_FORMAT_CRLF "Error: Header fields bad format. CRLF Missing !"
# define METHOD_LOWERCASE "Error: In Header Request-Line. Method is in lowercase."
# define METHOD_HOST_MISSING "400 Bad Request"
# define PROTOCOL_VERSION "HTTP/1.1"
# define DEFINED_TWICE "Error: Header Element Defined Twice"
# define BAD_CGI_VALUES "Error: CGI values are incorrect or missing"
# define CRLF "\r\n"
# define CR '\r'
# define LF '\n'

int error(std::string str, int i, Request *request);
void parsingClear(std::ifstream &flux, std::map<std::string, std::string> values, std::vector<std::string> body, std::string line);
void printCGI(std::map<std::string, std::string> cgi);
void print_map(std::map<std::string, std::string> mymap, std::vector<std::string> vec);

#endif
