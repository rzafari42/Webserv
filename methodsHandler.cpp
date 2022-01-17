/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methodsHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:12:49 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/17 12:22:05 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methodsHandler.hpp"


methodsHandler::methodsHandler() {}

methodsHandler::~methodsHandler() {}

methodsHandler::methodsHandler(const methodsHandler &src) {}

methodsHandler& methodsHandler::operator=(const methodsHandler& rhs) {}

//changer le retour evidemment
std::string	methodsHandler::handle_get_method(Request *req)
{
    HttpResponse resp;

    std::ifstream sourceFile(req->get_url(), std::ifstream::in);

    if (sourceFile.good())
    {
        std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
        resp.set_content(ans);
        resp.set_http_version("HTTP1.1");
        resp.set_status_code(200);
        resp.set_reasonPhrase("OK");
        resp.set_contentLength(resp.get_content().size());
    }
    else
    {
        std::cout << "404 NOT FOUND" << std::endl;
        std::ifstream sourceFile(req->get_url(), std::ifstream::in);
        if (sourceFile.good())
        {
            std::string ans((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>()));
            resp.set_content(ans);
            resp.set_http_version("HTTP1.1");
            resp.set_status_code(404);
            resp.set_reasonPhrase("Not Found");
            resp.set_contentLength(resp.get_content().size());
        }
        else
            std::cout << "error while searching for the right file" << std::endl;
    }
    sourceFile.close();
    resp.constructResponse();
}

std::string methodsHandler::handle_post_method(Request *req)
{
    
}

std::string methodsHandler::handle_delete_method(Request *req)
{
    
}
