/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:50:51 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/29 02:54:32 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "../../../Header/main_header.hpp"

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

#endif
