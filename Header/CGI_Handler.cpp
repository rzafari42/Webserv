/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:12:53 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/17 16:07:39 by simbarre         ###   ########.fr       */
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

char		**CGI_Handler::env_to_double_char(void)
{
	//transform _env t0 double char array
	char	**ret = new char*[this->_env.size() + 1];

	//with iterator, add element.first + '=' + element.second

	return (NULL);
}

std::string	CGI_Handler::run_CGI(const std::string &script)
{
	//this is the function to call to run the CGI

	pid_t			pid;
	std::string		ret_body;
	int				fd_saver[2];

	fd_saver[0] = dup(STDIN_FILENO);
	fd_saver[1] = dup(STDOUT_FILENO);

	pid = fork();

	if (pid == -1)
		return ("Status: 500\r\n\r\n");
	else if (pid == 0)
	{
		//needs all the dup and all

		char	**env = env_to_double_char();
		execve(script.c_str(), NULL, env);
	}
	else
	{
		int ret;
		waitpid(pid, &ret, 0);
		//yes sir
	}


	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);
	close(fd_saver[0]);
	close(fd_saver[1]);
	return (ret_body);
}
