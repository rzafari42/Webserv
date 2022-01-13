#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "Header/HttpResponse.hpp"

#define PORT 8080
int main(void)
{

    int server_fd = 0, new_socket = 0;

    struct sockaddr_in serv_addr, cli_addr;
    fd_set readset, cpy; //ensemble de fd
    int addrlen = sizeof(serv_addr);
    long valread;
    socklen_t len;
    pid_t childpid;
    char buffer[1024] = {0};
    std::ifstream file;
    int file_len = 0;

    char* message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";;
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    

    //int bind(int socket, const struct sockaddr *serv_addr, socklen_t serv_addr_len);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket cannot be created");
        return 0;
    }
    serv_addr.sin_family = AF_INET; //toujours égal à AF_INET. Indique les types d'addresses avec lesquels le socket communique (ici IPV4)
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //indique au socket de se lier à toutes les interfaces disponible
    serv_addr.sin_port = htons(PORT); //Port à contacter
    if (bind(server_fd, (struct sockaddr *)&serv_addr, addrlen) == -1) //liaison de la socket au point de commnication (adresse et port)
    {
        perror("Bind failed");
        return 0;
    }
    if ((listen(server_fd, 10) == -1)) //met le socket en attente
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    FD_ZERO(&readset); //efface l'ensemble readset
    FD_SET(server_fd, &readset); //met le fd: server_fd dans l'ensemble readset
    while (1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        cpy = readset;
        select(server_fd + 1, &cpy, NULL, NULL, NULL); //en attente du statut de lecture d'un fd dans l'ensemble readset. L'ensemble readset est modifié en sortie pour indiquer les fd qui ont changé d'état
        if (FD_ISSET(server_fd, &readset)) //verifie que server_fd soit bien dans l'ensemble readset. Si oui, server_fd est prêt
        {   
            len = sizeof(cli_addr);
            if ((new_socket = accept(server_fd, (struct sockaddr*)&serv_addr, (socklen_t*)&addrlen) == -1)) //Extrait la 1er connex° de la file d'attente de listen, crée une nouvelle socket et renvoie un fd faisant référence à cette socket. la sturucture cli_adrr sera remplie avec l'adresse du correspondant qui se connecte
            {
                perror("In accept");
                exit(EXIT_FAILURE);
            }
            if ((childpid = fork()) == 0)
            {
                    close(server_fd);
                    bzero(buffer, sizeof(buffer));
                    printf("Message From TCP client: \n");
                    valread = read(new_socket , buffer, 1024);
                    if(valread < 0)
                        printf("No bytes are there toread");
                    puts(buffer);
                    HttpResponse res("../Webpage/home.html");

                    std::string cont = res.getResponse();
                    char *buff = new char[cont.length()]; 
                    strcpy(buff, cont.c_str());
                    write(new_socket , buff, cont.length());
                    delete [] buff;
            }
            close(new_socket);
        }        
    }
    return 0;
}