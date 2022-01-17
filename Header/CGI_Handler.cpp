/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:12:53 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/17 15:09:00 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI_Handler.hpp"

CGI_Handler::CGI_Handler()
{
	_env["AUTH_TYPE"] = "";
	_env["CONTENT_LENGTH"] = "";
	_env["CONTENT_TYPE"] = "";
	_env["DOCUMENT_ROOT"] = "";
	_env["GATEWAY_INTERFACE"] = "";
	_env["HTTP_ACCEPT"] = "";
	_env["HTTP_COOKIE"] = "";							//stays NULL
	_env["HTTP_FROM"] = "";
	_env["HTTP_REFERER"] = "";
	_env["HTTP_USER_AGENT"] = "";
	_env["PATH_INFO"] = "";
	_env["PATH_TRANSLATED"] = "";
	_env["QUERY_STRING"] = "";
	_env["REMOTE_ADDR"] = "";
	_env["REMOTE_HOST"] = "";
	_env["REMOTE_IDENT"] = "";
	_env["REMOTE_USER"] = "";
	_env["REQUEST_METHOD"] = "";
	_env["SCRIPT_NAME"] = "";
	_env["SERVER_NAME"] = "webserv";					//change to hostname
	_env["SERVER_PORT"] = 8080;							//to change
	_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	_env["SERVER_SOFTWARE"] = "webserv/1.1";
}

CGI_Handler::CGI_Handler(CGI_Handler const &src) : _env(src._env)
{}

CGI_Handler	&CGI_Handler::operator=(CGI_Handler const &src)
{
	if (this != &src)
	{
		_env = this->_env;
	}
}

std::string	CGI_Handler::run_CGI(void)
{
	//this is the function to call to run the CGI

	pid_t		pid;
	std::string	ret_body;

	pid = fork();

	if (pid == -1)
		return (NULL);			//error (return Status: 500\r\n\r\n ??)
	else if (pid == 0)
	{
		//dup2
		//execve ?
		//write
		std::cout << "hm" << std::endl;
	}
	else
	{
		int ret;
		waitpid(pid, &ret, 0);
		//yes sir
	}

	return (ret_body);
}
