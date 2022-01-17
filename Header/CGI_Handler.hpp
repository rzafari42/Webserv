/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:13:00 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/17 14:58:20 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

#include "main_header.hpp"

	#include <sys/types.h>
	#include <sys/wait.h>

class	CGI_Handler
{
	public:
		CGI_Handler();
		CGI_Handler(CGI_Handler const &src);
		virtual	~CGI_Handler() {}

		CGI_Handler	&operator=(CGI_Handler const &src);

		std::string	run_CGI(void);	//see what to send to this function

	private:
		std::map<std::string, std::string>	_env;
};

#endif
