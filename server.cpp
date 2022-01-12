/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:01:31 by simbarre          #+#    #+#             */
/*   Updated: 2022/01/12 19:24:47 by simbarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SERVER_PORT			8080
#define BUFF_SIZE			4096
#define SERVER_BACKLOG		100

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>

//#include <conf/parsing/http_request_conf/utils.hpp>
//#include <conf/parsing/nginx_conf/utils.hpp>

typedef struct sockaddr		SA;
typedef struct sockaddr_in	SA_IN;

int		check(int exp, const char *msg)
{
	if (exp == -1 || exp < 0)
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

	while ((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer) - msg_size - 1)))
	{
		msg_size += bytes_read;
		if (msg_size > BUFF_SIZE - 1 || buffer[msg_size - 1] == '\n')
			break;
	}
	check(bytes_read, "recv error");
	buffer[msg_size - 1]  = 0;

	printf("REQUEST: %s\n", buffer);
	fflush(stdout);

	if (realpath(buffer, actual_path) == NULL)
	{
		printf("ERROR:(bad path): %s\n", buffer);
		close(client_socket);
		return (NULL);
	}

	FILE *fp = fopen(actual_path, "r");
	if (fp == NULL)
	{
		printf("ERROR");
		close(client_socket);
		return (NULL);
	}

	while ((bytes_read = fread(buffer, 1, BUFF_SIZE, fp)) > 0)
		write(client_socket, buffer, bytes_read);

	close(client_socket);
	fclose(fp);
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

	SA_IN	server_addr;

	check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket.");

	server_addr.sin_family		= AF_INET;
	server_addr.sin_addr.s_addr	= INADDR_ANY;
	server_addr.sin_port		= htons(port);

	check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)), "Bind failed!");

	check(listen(server_socket, backlog), "Listen failed!");

	return (server_socket);
}

int		main(int argc, char *argv[])
{
	int server_socket = setup_server(SERVER_PORT, SERVER_BACKLOG);

	fd_set		current_sockets, ready_sockets;

	FD_ZERO(&current_sockets);
	FD_SET(server_socket, &current_sockets);

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
	return (0);
}
