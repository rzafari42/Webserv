/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:01:31 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/26 17:15:32 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SERVER_PORT			8080
#define BUFF_SIZE			4096
#define SERVER_BACKLOG		100

#include "Header/main_header.hpp"

typedef struct sockaddr		SA;
typedef struct sockaddr_in	SA_IN;

int		check(int exp, const char *msg)
{
	if (exp < 0)
	{
		perror(msg);
		exit(1);
	}
	return (exp);
}

//pour l'instant cette fonction affiche juste la requette qu'elle recoit
//ajouter parsing de la requette et tt le reste
void	*handle_connection(int client_socket)
{
	char	buffer[BUFF_SIZE];
	size_t	bytes_read;
	int		msg_size = 0;
	char	actual_path[PATH_MAX + 1];
	static int i = 0;

	while ((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer) - msg_size - 1)))
	{
		msg_size += bytes_read;
		if (msg_size > BUFF_SIZE - 1 || buffer[msg_size - 1] == '\n')
			break;
	}
	check(bytes_read, "recv error");
	buffer[msg_size - 1]  = 0;

	printf("REQUEST: \n%s\n", buffer);
	fflush(stdout);

	//Name file creation
	std::string namefile = "Request_";
	namefile.append(std::to_string(i));
	namefile.append(".txt");
	i++;

	std::ofstream myfile;
	myfile.open(namefile, std::ofstream::app);
	std::string str(buffer);
	myfile << str; //Write the request in a file
	myfile.close();
	Request req = req_parsing(namefile); //Parsing
	std::remove(namefile.c_str());

	HttpResponse res(&req);
	std::string cont = res.getResponse();
	char *buff = new char[cont.length()];
	strcpy(buff, cont.c_str());
	
	write(client_socket , buff, cont.length()); //Envoie de la reponse au client
	delete [] buff;
	close(client_socket);
	printf("closing connection\n");
	return (NULL);
}

int		accept_new_connection(int server_socket)
{
	int		addr_size = sizeof(SA_IN);
	int		client_socket;
	SA_IN	client_addr;

	check(client_socket = accept(server_socket, (SA*)&client_socket, (socklen_t*)&addr_size), "Accept!");

	return (client_socket);
}

int		setup_server(short port, int backlog)
{
	int		server_socket, client_socket, addr_size;
	int		opt = 1;

	SA_IN	server_addr;

	check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket.");
	check(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)), "Setsockopt failed!");
	check(fcntl(server_socket, F_SETFL, O_NONBLOCK), "fcntl() failed!");

	server_addr.sin_family		= AF_INET;
	server_addr.sin_addr.s_addr	= INADDR_ANY;
	server_addr.sin_port		= htons(port);

	check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)), "Bind failed!");
	check(listen(server_socket, backlog), "Listen failed!");

	return (server_socket);
}

void get_port(std::string *port, std::string address)
{
	std::string::iterator it = address.begin();
	std::string::iterator ite = address.end();

	while (*it != ':')
		it++;
	it++;
	while (it != ite)
	{
		port->push_back(*it);
		it++;
	}
}

static int stringToInt(std::string s ) 
{
    int i;
    std::istringstream(s) >> i;
    return i;
}

//nc -c localhost 8080 
int		main(int argc, char *argv[])
{
	if (argc > 1)
	{
		std::vector<ServerInfo> conf; 
		ParserConf parser;
		int		server_socket = 0;
		std::string address = "";
		std::string port = "";
		fd_set	current_sockets, ready_sockets;


		parser.parse(argv[1], &conf);

		std::vector<ServerInfo>::iterator it = conf.begin();
		std::vector<ServerInfo>::iterator ite = conf.end();
		
		FD_ZERO(&current_sockets);
			std::cout << "main00\nit = " << it->get_listen() << "\nite : " << ite->get_listen() << std::endl;
		while (it != ite)
		{	
			port.clear();
			address.clear();
			address = it->get_listen();
			std::cout << address << std::endl;
			get_port(&port, address);
			std::cout << "port : " << port << std::endl;
			server_socket = setup_server(stringToInt(port), SERVER_BACKLOG);
			FD_SET(server_socket, &current_sockets);
			it++;
		}
		
		/*server_socket = setup_server(SERVER_PORT, SERVER_BACKLOG);


		FD_ZERO(&current_sockets);
		FD_SET(server_socket, &current_sockets);*/
		
		while (true)
		{
			ready_sockets = current_sockets;

			check(select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL), "Failed to select");

			for (int i = 0; i < FD_SETSIZE; i++)
			{
				if (FD_ISSET(i, &ready_sockets))
				{
					if (i == server_socket)
					{
						//new connection
						int client_socket = accept_new_connection(server_socket);
						FD_SET(client_socket, &current_sockets);
					}
					else
					{
						handle_connection(i);
						FD_CLR(i, &current_sockets);
					}
				}
			}
		}
	}
	else
		std::cout << "Configuraion File might be missing !" << std::endl;
	return (0);
}
