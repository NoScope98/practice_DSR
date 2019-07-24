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

int main(int argc, char *argv[])
{
    char buf[1500];
    int sockfd;
    int len;

    struct sockaddr_in serv;
    struct sockaddr_in cliaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(0);
    }

    printf("Socket has been created\n");
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(ADDRESS);

    while (1)
    {
        printf("Enter the message: ");
        fgets(buf, sizeof(buf), stdin);

        len = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&serv, sizeof(serv));

        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);

        buf[len] = '\0';
	printf("Recieved: '%s'\n", buf);
    }

    close(sockfd);
    return 0;
}
