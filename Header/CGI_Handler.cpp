/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:12:53 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/31 04:14:07 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI_Handler.hpp"

CGI_Handler::CGI_Handler(Request &request, ParserConf &conf) : _req(request), _conf(conf)
{
	std::vector<std::string> tmp = request.get_body();

	for (std::vector<std::string>::const_iterator i = tmp.begin();
		i != tmp.end(); ++i)
		_body += *i;

	_env["AUTH_TYPE"]			= "";					//no security
	_env["CONTENT_LENGTH"]		= _body.length();
	_env["CONTENT_TYPE"]		= "";					//MIME type of the body of the request
	_env["GATEWAY_INTERFACE"]	= "CGI/1.1";
	_env["PATH_INFO"]			= "";					//identifies the resource or sub-resource to be returned by the CGI script, and it is derived from the portion of the URI path following the script name but preceding any query data
	_env["PATH_TRANSLATED"]		= "";					//Maps the script's virtual path to the physical path used to call the script
	_env["QUERY_STRING"]		= "";					//The query string that is contained in the request URL after the path.
	_env["REDIRECT_STATUS"]		= "200";
	_env["REQUEST_METHOD"]		= "";					//request.get_method();
	_env["SCRIPT_NAME"]			= "";					//conf.script_name;
	_env["SERVER_NAME"]			= "webserv";			//conf.server_name;
	_env["SERVER_PORT"]			= "8080";
	_env["SERVER_PROTOCOL"]		= "HTTP/1.1";
	_env["SERVER_SOFTWARE"]		= "webserv/1.1";
}														//we'll see if we need more env var

CGI_Handler::CGI_Handler(CGI_Handler const &src) : _env(src._env)
{}

CGI_Handler	&CGI_Handler::operator=(CGI_Handler const &src)
{
	if (this != &src)
	{
		_env = src._env;
	}
	return (*this);
}

std::string	file_to_str(std::string in)
{
	std::ifstream		t(in.c_str());
	std::stringstream	buffer;

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

	if (pipe(pipe_fd))
		exit(EXIT_FAILURE);								//add more error management

	pid = fork();
	if (pid == -1)
		return ("Status: 500\r\n\r\n");
	else if (pid == 0)
	{
		char	**env = env_to_double_char();
		char	*args[2];

		args[0] = strdup(script.c_str());				//modified this, should work as expected
		args[1] = NULL;

		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);

		int	fd_tmp = open("/tmp/cgi_output", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

		dup2(fd_tmp, 1);
		dup2(fd_tmp, 2);
		if (execve(args[0], args, env) == -1)
			exit(EXIT_FAILURE);							//add more error management
		close(0);
		close(fd_tmp);
		close(pipe_fd[0]);
		exit(0);

		free(args[0]);
		delete [] env;									//see if this deletes all
	}
	else
	{
		close(pipe_fd[0]);
		write(pipe_fd[1], _body.c_str(), _body.length());
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);							//everyone uses -1 instead of pid, maybe move it at the top ?
	}

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);
	close(fd_saver[0]);
	close(fd_saver[1]);

	if (pid == 0)
		exit(0);

	return (file_to_str("/tmp/cgi_output"));
}
