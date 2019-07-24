#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 55555
#define ADDRESS "127.0.0.1"
#define BUF_LEN 1500

int main(int argc, char *argv[])
{
    char buf[BUF_LEN];
    char message[BUF_LEN];
    int sockfd;

    struct sockaddr_in serv;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(0);
    }

    printf("Socket has been created\n");
    memset(&serv, 0, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(ADDRESS);

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Error connect\n");
        exit(0);
    }

    while (1)
    {
        printf("Enter the message: ");
        fgets(message, sizeof(message), stdin);

        send(sockfd, message, sizeof(message), 0);
        recv(sockfd, buf, sizeof(message), 0);

        printf("Received: %s", buf);
    }

    close(sockfd);
    return 0;
}
