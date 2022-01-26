/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:13:00 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/26 14:48:05 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

#include "main_header.hpp"

	#include <sys/types.h>			//include in main_header at the end
	#include <sys/wait.h>			//same

class	CGI_Handler
{
	public:
		CGI_Handler(Request &request, ParserConf &conf);
		CGI_Handler(CGI_Handler const &src);
		virtual	~CGI_Handler() {}

		CGI_Handler	&operator=(CGI_Handler const &src);

		std::string	run_CGI(const std::string &script);	//see what to send to this function
		char		**env_to_double_char(void);

	private:
		std::map<std::string, std::string>	_env;
		Request								_req;
		ParserConf							_conf;
		std::string							_body;
};

#endif
