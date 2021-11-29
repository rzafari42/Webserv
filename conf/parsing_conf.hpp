/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_conf.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:22:49 by rzafari           #+#    #+#             */
/*   Updated: 2021/11/26 17:26:33 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_CONF_HPP
# define PARSING_CONF_HPP
# include <iostream>

struct s_conf{
    std::string server_name;
    std::string error_page;
    std::string listen;
    std::string error_page;
    size_t      client_max_body_size;
    std::string autoindex;
    std::string index;
    std::string root;

};

class conf
{
    public:
        conf();
        conf(const conf &src);
        conf & operator=(const conf &src);
        ~conf();

    private:


};

#endif