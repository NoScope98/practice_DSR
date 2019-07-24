#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 55555

int main(int argc, char *argv[])
{
    char buf[1500];

    int sockfd;
    int len;
    int len2;

    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(0);
    }

    printf("Socket has been creating\n");
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Error binding socket\n");
        exit(0);
    }

    printf("Socket has bound\n");
    len = sizeof(cliaddr);

    while (1)
    {
        //strcpy(buf, " ");
	len2 = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);

        buf[len2] = '\0';

        printf("Received: '%s' from client\n", buf);
        sendto(sockfd, buf, len2, 0, (struct sockaddr *)&cliaddr, len);
    }
    return 0;
}
