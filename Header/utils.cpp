/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:50:51 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/31 04:31:46 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main_header.hpp"

int error(std::string str, int i, Request *request)
{
    if(i == 1)
        request->set_isErrorSyntax();
    std::cout << str << std::endl;
    return -1;
}

void parsingClear(std::ifstream &flux, std::map<std::string, std::string> values, std::vector<std::string> body, std::string line)
{
    line.clear();
    values.clear();
    body.clear();
    flux.close();
}

void printCGI(std::map<std::string, std::string> cgi)
{
    std::map<std::string,std::string>::iterator it;
    for (it = cgi.begin(); it != cgi.end(); ++it)
        std::cout << it->first << ": " << it->second << '\n';
}

void print_map(std::map<std::string, std::string> mymap, std::vector<std::string> vec)
{
    std::map<std::string,std::string>::iterator it;

    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << ": " << it->second << '\n';

    std::vector<std::string>::iterator it_vec = vec.begin();
    std::vector<std::string>::iterator ite_vec = vec.end();

    while(it_vec != ite_vec)
    {
        std::cout << *it_vec << std::endl;
        it_vec++;
    }
}
