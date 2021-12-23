#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
int main(void)
{

    int server_fd = 0, new_socket = 0;

    struct sockaddr_in serv_addr, cli_addr;
    fd_set readset;
    int fd_ready;
    int addrlen = sizeof(serv_addr);
    long valread;
    socklen_t len;
    pid_t childpid;
    char buffer[1024] = {0};

    char* message = "Hello Client (Redwwane)";
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    

    //int bind(int socket, const struct sockaddr *serv_addr, socklen_t serv_addr_len);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket cannot be created");
        return 0;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&serv_addr, addrlen) == -1)
    {
        perror("Bind failed");
        return 0;
    }
    if ((listen(server_fd, 10) == -1))
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    FD_ZERO(&readset);
    while (1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        FD_SET(server_fd, &readset);
        fd_ready = select(server_fd + 1, &readset, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readset))
        {   
            len = sizeof(cli_addr);
            if ((new_socket = accept(server_fd, (struct sockaddr*)&cli_addr, &len) == -1))
            {
                perror("In accept");
                exit(EXIT_FAILURE);
            }
            if ((childpid = fork()) == 0)
            {
                    close(server_fd);
                    bzero(buffer, sizeof(buffer));
                    printf("Message From TCP client: ");
                    valread = read(new_socket , buffer, 1024);
                    printf("%s\n",buffer);
                    if(valread < 0)
                    { 
                        printf("No bytes are there to read");
                    }
                    write(new_socket , (const char*)message , sizeof(buffer));
                    printf("------------------Hello message sent-------------------\n");
                    close(new_socket);
                    exit(0);
            }
            close(new_socket);
        }
        
    }
    return 0;
}