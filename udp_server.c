#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define BUF_LEN 1500

int configure(int port)
{
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error creating socket\n");
        exit(0);
    }
    printf("Socket has been creating\n");

    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket\n");
        exit(0);
    }
    printf("Socket has bound\n");

    return sockfd;
}

void run(int sockfd)
{
    char buf[BUF_LEN];
    int len;
    int len2;

    struct sockaddr_in cliaddr;

    len = sizeof(cliaddr);

    while (1)
    {
	len2 = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);

        buf[len2] = '\0';

        printf("Received: '%s' from client\n", buf);
        sendto(sockfd, buf, len2, 0, (struct sockaddr *)&cliaddr, len);
    }
}

/*
int main(int argc, char *argv[])
{
    int sockfd = configure(55555);
    run(sockfd);
    return 0;
}
*/
