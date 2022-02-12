#include "CGI_Handler.hpp"

CGI_Handler::CGI_Handler(Request &request, ServerInfo &conf, Location &loc) : _req(request), _conf(conf), _loc(loc)
{
	_body = request.get_body();

	std::cout << "my body is ready : " << _body << std::endl;

	_env["AUTH_TYPE"]			= "";
	_env["CONTENT_TYPE"]		= _req.get_contentType();
	_env["GATEWAY_INTERFACE"]	= "CGI/1.1";
	_env["QUERY_STRING"]		= _req.get_cgi();
	_env["REDIRECT_STATUS"]		= "200";
	_env["REQUEST_METHOD"]		= _req.get_method();
	_env["REQUEST_URI"]			= _loc.get_uri();
	if (_req.get_method() == "GET")
		_env["CONTENT_LENGTH"]		= "0";
	else if (_req.get_method() == "POST")
		_env["CONTENT_LENGTH"]		= _body.length();
	_env["SCRIPT_NAME"]			= _loc.get_cgi_path();
	_env["SERVER_NAME"]			= _conf.get_server_name();
	std::ostringstream s;
	s << _conf.get_listen();
	_env["SERVER_PORT"]			= s.str();
	_env["SERVER_PROTOCOL"]		= "HTTP/1.1";
	_env["SERVER_SOFTWARE"]		= "webserv/1.1";
	_env["DIR_PATH"]			= _loc.get_root();

	_env["REMOTE_ADDR"]			= "0.0.0.0";		//get client IP
	_env["REMOTE_HOST"]			= "";				//can be left empty
	_env["REMOTE_IDENT"]		= "";				//can be left empty
	_env["REMOTE_USER"]			= "";				//can be left empty
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
	char	**ret = new char*[this->_env.size() + 1];

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
	return (ret);
}

std::string	CGI_Handler::run_CGI(const std::string &script)
{
	int fdOut[2];
	int fdIN[2];
	std::string msgbody;

	std::cout << "BODY = [" << _req.get_body() << "]" << std::endl;

	_env["PATH_INFO"]			= script;
	_env["PATH_TRANSLATED"]		= script;

	if (pipe(fdOut) < 0 || pipe(fdIN) < 0)
		std::cout << "pipe failed in executeCGI method" << std::endl;

	pid_t pid = fork();

	if (!pid){ // in child

		char	**env = env_to_double_char();
		char	*args[2];

		args[0] = (char*)"/mnt/c/Users/simon/Documents/42/webserv/cgi_bin/php-cgi7.2";
		args[1] = (char*)"-c";
		args[2] = (char*)"/mnt/c/Users/simon/Documents/42/webserv/cgi_bin/php.ini";
		args[3] = (char*)script.c_str();
		args[4] = NULL;

		// stdout is now a copy of fdOut[1] and in case post method, stdin is a copy of fdIn[0]
		dup2(fdOut[1], STDOUT_FILENO);
		close(fdOut[0]);
		close(fdOut[1]);

		dup2(fdIN[0], STDIN_FILENO);
		close(fdIN[0]);
		close(fdIN[1]);

		// change the repo into where the program is
		chdir(this->_loc.get_root().c_str());

		if (execve(args[0], args, env) < 0){
			exit(-1);
		}

		delete [] env;
	}
	else if (pid > 0){ // in parent

		close(fdOut[1]);
		write(fdIN[1], _body.c_str(), _body.length());
		close(fdIN[1]);
		close(fdIN[0]);

        // Checking if execve correctly worked
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == -1)
			std::cerr << "error: execve failed in executeCGI method" << std::endl;
		char buf[64 + 1] = {0};
		while (read(fdOut[0], buf, 64) > 0)
		{
			msgbody += buf;
			memset(buf, 0, 64 + 1);
		}
		msgbody += buf;

		close(fdOut[0]);
	}
	else{
		close(fdOut[1]);
		close(fdOut[0]);
		if (this->_req.get_method() == "POST")
		{
			close(fdIN[0]);
			close(fdIN[1]);
		}
		std::cout << "fork failed executeCGI method" << std::endl;
	}

	return msgbody;

}

