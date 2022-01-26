/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methodsHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:39:44 by rzafari           #+#    #+#             */
/*   Updated: 2022/01/17 12:21:55 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODSHANDLER_HTPP
# define METHODSHANDLER_HTPP
# include "conf/parsing/http_request_conf/parsing_http.hpp"
# include "Header/main_header.hpp"

class methodsHandler
{
    public:
        methodsHandler();
        methodsHandler(const methodsHandler &src);
        methodsHandler &operator=(const methodsHandler& rhs);
        ~methodsHandler();

        std::string handle_get_method(Request *req);
        std::string handle_post_method(Request *req);
        std::string handle_delete_method(Request *req);
};

#endif