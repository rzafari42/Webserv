/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:48:51 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/29 02:54:45 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "../../../Header/main_header.hpp"

class Location
{
private:
    std::string uri;
    std::string root;
    std::string index;
    std::string autoindex;
    std::size_t return_code;
    std::string return_path;
    std::string cgi_extension;
    std::string cgi_path;
    std::vector<std::string> methods;
public:
    // constructor/ destructor
    Location( void ) : return_code(0) {
        uri.clear();
        methods.clear();
        root.clear();
        index.clear();
        autoindex.clear();
        return_path.clear();
        cgi_extension.clear();
        cgi_path.clear();
    }
    ~Location() {}

    // getters
    std::vector<std::string> get_methods( void ) { return methods; }

    std::vector<std::string> *get_ptr_methods( void ) { return &methods; }

    std::string get_uri( void ) { return uri; }
    std::string get_root( void ) { return root; }

    std::string get_index( void ) { return index; }

    std::string get_autoindex( void ) { return autoindex; }

    std::size_t get_return_code( void ) { return return_code; }

    std::string get_return_path( void ) { return return_path; }

    std::string get_cgi_extension( void ) { return cgi_extension; }

    std::string get_cgi_path( void ) { return cgi_path; }

    // setters
    void set_uri( std::string str ) { uri = str; }

    void set_root( std::string str ) { root = str; }

    void set_index( std::string str ) { index = str; }

    void set_autoindex( std::string str ) { autoindex = str; }

    void set_return_code( size_t n ) { return_code = n; }

    void set_return_path( std::string str ) { return_path = str; }

    void set_cgi_extension( std::string str ) { cgi_extension = str; }

    void set_cgi_path( std::string str ) { cgi_path = str; }
};

    void set_cgi_path( std::string str ) { cgi_path = str; }
};

#endif
