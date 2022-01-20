/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:12:53 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/20 07:32:17 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI_Handler.hpp"

CGI_Handler::CGI_Handler()								//left to fill all of this with the parser
{
	_env["AUTH_TYPE"]			= "";
	_env["CONTENT_LENGTH"]		= "";
	_env["CONTENT_TYPE"]		= "";
	_env["DOCUMENT_ROOT"]		= "";
	_env["GATEWAY_INTERFACE"]	= "CGI/1.1";
	_env["HTTP_ACCEPT"]			= "";
	_env["HTTP_COOKIE"]			= "";					//stays NULL
	_env["HTTP_FROM"]			= "";
	_env["HTTP_REFERER"]		= "";
	_env["HTTP_USER_AGENT"]		= "";
	_env["PATH_INFO"]			= "";
	_env["PATH_TRANSLATED"]		= "";
	_env["QUERY_STRING"]		= "";
	_env["REMOTE_ADDR"]			= "";
	_env["REMOTE_HOST"]			= "";
	_env["REMOTE_IDENT"]		= "";
	_env["REMOTE_USER"]			= "";
	_env["REQUEST_METHOD"]		= "";
	_env["SCRIPT_NAME"]			= "";
	_env["SERVER_NAME"]			= "webserv";			//change to hostname
	_env["SERVER_PORT"]			= 8080;
	_env["SERVER_PROTOCOL"]		= "HTTP/1.1";
	_env["SERVER_SOFTWARE"]		= "webserv/1.1";
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

std::string	file_to_str(std::string in)
{
	std::ifstream t(in);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return (buffer.str());
}

char		**CGI_Handler::env_to_double_char(void)
{
	char	**ret = new char*[this->_env.size() + 1];

	std::map<std::string, std::string>::iterator it = _env.begin();

	int i = 0;
	while (it != _env.end())
	{
		std::string tmp = it->first;
		tmp.append("=");
		tmp.append(it->second);
		ret[i] = new char[tmp.length()];
		tmp.copy(ret[i++], tmp.length(), 0);
		++it;
	}													//to test, first tried with strdup but can it *delete* ? idk

	return (ret);
}

std::string	CGI_Handler::run_CGI(const std::string &script)
{														//add here the parsed request or add it as a member
	pid_t	pid;
	int		fd_saver[2];
	int		pipe_fd[2];									//not everybody uses pipes, but it makes more sense to me

	fd_saver[0] = dup(STDIN_FILENO);
	fd_saver[1] = dup(STDOUT_FILENO);

	pipe(pipe_fd); //add error check

	pid = fork();
	if (pid == -1)
		return ("Status: 500\r\n\r\n");
	else if (pid == 0)
	{
		char	**env = env_to_double_char();
		char	*args[] = { NULL };						//maybe change it ? is it usefull ?

		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);

		int	fd_tmp = open("/tmp/cgi_output", O_RDWR);	//add lots more things here + error check, this is the file where the output is going to be stored then read
		dup2(fd_tmp, 1);
		dup2(fd_tmp, 2);
		execve(script.c_str(), args, env);				//add error check + maybe do something else with args ?
		close(0);
		close(fd_tmp);
		close(pipe_fd[0]);
		exit(0);
		delete [] env;									//see if this deletes all
	}
	else
	{
		close(pipe_fd[0]);
		//write(fd[1], request.body.c_str(), request.body.lenght()); //here, write the request body to the file in tmp (MOST IMPORTANT PART LOL)
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);							//everyone uses -1 insted of pid
	}

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);
	close(fd_saver[0]);
	close(fd_saver[1]);

	if (pid == 0)
		exit(0);

	return (file_to_str("/tmp/cgi_output"));
}
