/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:13:24 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/18 14:33:41 by rzafari          ###   ########.fr       */
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
# define HTTP_VERSION "HTTP1.1"
# define HOME_PAGE_PATH  "/index.html"

#include "../conf/parsing/http_request_conf/parsing_http.hpp"
#include "HttpResponse.hpp"
/*#include "conf/parsing/http_request_conf/utils.hpp"
#include "conf/parsing/nginx_conf/utils.hpp"*/

#endif
