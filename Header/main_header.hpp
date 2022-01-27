/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:13:24 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/26 15:01:18 by simbarre         ###   ########.fr       */
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
# define HTTP_VERSION "HTTP/1.1"
# define HOME_PAGE_PATH  "/index.html"

#include "../conf/parsing/http_request_conf/parsing_http.hpp"
#include "../conf/parsing/nginx_conf/ParserConf.hpp"
#include "HttpResponse.hpp"
#include "CGI_Handler.hpp"
/*#include "conf/parsing/http_request_conf/utils.hpp"
#include "conf/parsing/nginx_conf/utils.hpp"*/

#endif
