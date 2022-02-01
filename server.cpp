/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:01:31 by simbarre          #+#    #+#             */
/*   Updated: 2022/02/01 09:20:00 by rzafari          ###   ########.fr       */
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
void	*handle_connection(int client_socket, ServerInfo conf)
{
	char	buffer[BUFF_SIZE];
	size_t	bytes_read;
	int		msg_size = 0;
	char	actual_path[PATH_MAX + 1];
	static int i = 0;
	std::vector<Location> loc;

	loc = conf.get_locations();

	std::vector<Location>::iterator it = loc.begin();
	std::vector<Location>::iterator ite = loc.end();

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

	HttpResponse res(&req, &conf);
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
	
//nc -c localhost 8080
int		main(int argc, char *argv[])
{
	if (argc > 1)
	{
		std::vector<ServerInfo> conf;
		ParserConf parser;
		std::map<ServerInfo, int> server_socket;
		std::map<int, ServerInfo> client_socket;
		fd_set	current_sockets, ready_sockets;
    	std::cout << "URL: " << std::endl;


		parser.parse(argv[1], &conf);

		std::vector<ServerInfo>::const_iterator it = conf.begin();
		std::vector<ServerInfo>::const_iterator ite = conf.end();
		FD_ZERO(&current_sockets);
		while (it != ite)
		{
			server_socket.insert(std::make_pair(*it, setup_server(it->get_listen(), SERVER_BACKLOG)));
			it++;
		}
		std::map<ServerInfo, int>::iterator it_m = server_socket.begin();
		std::map<ServerInfo, int>::iterator it_me = server_socket.end();
		while (it_m != it_me)
		{
			FD_SET(it_m->second, &current_sockets);
			it_m++;
		}
		while (true)
		{
			ready_sockets = current_sockets;
			check(select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL), "Failed to select");

			for (int i = 0; i < FD_SETSIZE; i++)
			{
				it_m = server_socket.begin();
				it_me = server_socket.end();
				if (FD_ISSET(i, &ready_sockets))
				{
					while (it_m != it_me)
					{
						if (i == it_m->second)
						{
							int new_client_socket = accept_new_connection(i);
							FD_SET(new_client_socket, &current_sockets);
							client_socket.insert(std::pair<int, ServerInfo>(new_client_socket, it_m->first));
							break;
						}
						it_m++;
					}
					if (it_m == it_me)
					{
						handle_connection(i, (client_socket.at(i)));
						FD_CLR(i, &current_sockets);
						client_socket.erase(i);
					}
				}
			}
		}
		server_socket.clear();
	}
	else
		std::cout << "Configuraion File might be missing !" << std::endl;
	return (0);
}