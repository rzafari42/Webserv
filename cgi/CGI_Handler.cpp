#include "CGI_Handler.hpp"
#include <sstream>

std::string s;
std::stringstream out;


CGI_Handler::CGI_Handler(Request &request, ServerInfo &conf, Location &loc) : _req(request), _conf(conf), _loc(loc)
{
	int i = 0;

	_env = new char*[16];
	std::stringstream out;
	_body = request.get_body();
	out << _body.size();
	std::string tmp;
	tmp = "CONTENT_LENGTH=";
	if (_req.get_method() == "GET")
		tmp += "0";
	else if (!_req.get_method().compare("POST"))
		tmp += out.str(); 
	_env[i++] = strdup(tmp.c_str());
	tmp = "CONTENT_TYPE=" + _req.get_contentType();
	_env[i++] = strdup(tmp.c_str());
	_env[i++] = strdup("GATEWAY_INTERFACE=CGI/1.1");
	//tmp = "PATH_INFO=" + ;
	//_env[i++] = strdup(tmp.c_str());
	//tmp = "PATH_TRANSLATED=" + ;
	//_env[i++] = strdup(tmp.c_str());
	_env[i++] = strdup("REDIRECT_STATUS=200");
	if (_req.get_method() == "GET")
		_env[i++] = strdup("REQUEST_METHOD=GET");
	else if (_req.get_method()== "POST")
		_env[i++] = strdup("REQUEST_METHOD=POST");
	//tmp = "REQUEST_URI=" + pathFile;
	//_env[i++] = strdup(tmp.c_str());
	_env[i++] = strdup("SERVER_NAME=servername");
	std::stringstream out1;
	int port = conf.get_listen();
	out1 << port;
	tmp = "SERVER_PORT=" + out1.str();
	_env[i++] = strdup(tmp.c_str());
	_env[i++] = strdup("SERVER_PROTOCOL=HTTP/1.1");
	_env[i++] = strdup("SERVER_SOFTWARE=webserv/1.1");
	_env[i++] = strdup(_loc.get_root().c_str());

	tmp = "QUERY_STRING" + _req.get_cgi();
	_env[i++] = strdup(tmp.c_str());
	_env[i++] = strdup("REMOTE_ADDR=0.0.0.0");
	_env[i] = NULL;

	std::cout << ">>>>>>>>>>>>LENGHT:" << _env[0] << std::endl;
}

CGI_Handler::CGI_Handler(CGI_Handler const &src) : _env(src._env)
{}

CGI_Handler	&CGI_Handler::operator=(CGI_Handler const &src)
{
	if (this != &src)
	{
		_env = src._env;
		_loc = src._loc;
		_conf = src._conf;
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
	/*char	**ret = new char*[this->_env.size() + 1];

	std::map<std::string, std::string>::iterator it = _env.begin();

	int i = 0;
	while (it != _env.end())
	{
		std::string tmp = it->first;
		tmp.append("=");
		tmp.append(it->second);
		ret[i] = new char[tmp.length()];
		tmp.copy(ret[i], tmp.length(), 0);
		ret[i++][tmp.length()] = '\0';
		tmp.clear();
		++it;									//to test, first tried with strdup but can it *delete* ? idk
	}
	return (ret);*/
	return NULL;
}

std::string	CGI_Handler::run_CGI(const std::string &script)
{
	pid_t	pid;
	int		fd_saver[2];
	int		pipe_fd[2];									//not everybody uses pipes, but it makes more sense to me

	//_env["PATH_INFO"]			= script;
	//_env["PATH_TRANSLATED"]		= script;
	//std::cout << "CGI script: " << _env["SCRIPT_NAME"] << std::endl;
	//std::cout << "CGI method: " << _env["REQUEST_METHOD"] << std::endl;

	fd_saver[0] = dup(STDIN_FILENO);
	fd_saver[1] = dup(STDOUT_FILENO);


	if (pipe(pipe_fd))
		exit(EXIT_FAILURE);								//add more error management

	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0)
	{

		//char	**env = env_to_double_char();

		/*std::map<std::string, std::string>::iterator it = _env.begin();
		int i = 0;
		for (; it != _env.end(); it++)
		{
			std::cout << env[i] << std::endl;
			i++;
		}*/
		char	*args[2];

		args[0] = (char*)script.c_str();
		args[1] = NULL;


		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);

		int	fd_tmp = open("/tmp/cgi_output", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

		if (fd_tmp < 0)
			return (NULL);
		dup2(fd_tmp, 1);
		//std::cout << "args[0]=" << args[0] << std::endl;
		if (execve(args[0], args, _env) == -1) {
			perror("error:");
			return (NULL);
		}
		close(0);
		close(fd_tmp);
		close(pipe_fd[0]);

		delete [] _env;

		exit(0);
	}
	else
	{
		close(pipe_fd[0]);
		write(pipe_fd[1], _body.c_str(), _body.length());
		close(pipe_fd[1]);
		int status = 0;
        waitpid(pid, &status, 0);						//everyone uses -1 instead of pid, maybe move it at the top ?
	}

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);
	close(fd_saver[0]);
	close(fd_saver[1]);

	if (pid == 0)
		exit(0);

	return (file_to_str("/tmp/cgi_output"));
}

