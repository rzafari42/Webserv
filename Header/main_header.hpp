/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:13:24 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/29 06:31:50 by simbarre         ###   ########.fr       */
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

# define HTTP_VERSION "HTTP/1.1"

# define HOME_PAGE_PATH "/index.html"
# define ERROR_400_PATH "/error400.html"
# define ERROR_404_PATH "/error404.html"
# define ERROR_411_PATH "/error411.html"
# define ERROR_505_PATH "/error505.html"

# define FILE_DELETED "/file_deleted.html"

#include "../conf/parsing/http_request_conf/parsing_http.hpp"
#include "../conf/parsing/http_request_conf/utils.hpp"
#include "../conf/parsing/nginx_conf/Location.hpp"
#include "../conf/parsing/nginx_conf/ServerInfo.hpp"
#include "../conf/parsing/nginx_conf/ParserConf.hpp"
#include "HttpResponse.hpp"
#include "CGI_Handler.hpp"

#endif
