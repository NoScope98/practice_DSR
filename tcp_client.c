#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define BUF_LEN 1500

int configure_tcp_client(int port, char *address)
{
    int sockfd;
    struct sockaddr_in serv;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error creating socket\n");
        exit(0);
    }
    printf("Socket has been created\n");

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = inet_addr(address);

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Error connect\n");
        exit(0);
    }

    return sockfd;
}

void run_tcp_client(int sockfd)
{
    char buf[BUF_LEN];
    char message[BUF_LEN];

    while (1)
    {
        printf("Enter the message: ");
        fgets(message, sizeof(message), stdin);

        send(sockfd, message, sizeof(message), 0);
        recv(sockfd, buf, sizeof(message), 0);

        printf("Received: %s", buf);
    }
    close(sockfd);
}
