/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_nginx.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:22:49 by rzafari           #+#    #+#             */
/*   Updated: 2021/12/21 17:22:10 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_CONF_HPP
# define PARSING_CONF_HPP
# include <iostream>
# include <fstream>
# include <vector>

struct s_location {
    std::string root;
    std::string index;
    std::string autoindex;
    std::string error_page;
    size_t      client_max_body_size;
    std::vector<std::string> methods;
};

struct s_server
{
    size_t nb_closing_br;
    size_t nb_server;
    size_t nb_location;
    std::string listen;
    std::string root;
    std::string index;
    std::string error_page;
    std::string server_name;
    std::string autoindex;
    size_t      client_max_body_size;
    s_location location;
};

#endif