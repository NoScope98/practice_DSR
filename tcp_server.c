#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 55555
#define BUF_LEN 1500

int main(int argc, char *argv[])
{
    char buf[BUF_LEN];

    int listener;
    int sockfd;
    int len;
    int len2;

    struct sockaddr_in servaddr;

    if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(0);
    }

    printf("Socket has been creating\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Error binding socket\n");
        exit(0);
    }
    printf("Socket has bound\n");

    listen(listener, 1);

    while (1)
    {
        if ((sockfd = accept(listener, NULL, NULL)) < 0)
        {
            printf("Error accept");
            exit(0);
        }

        while (1)
        {
            len = recv(sockfd, buf, sizeof(buf), 0);
            printf("Received: '%s' from client\n", buf);
            if (len <= 0)
                break;
            send (sockfd, buf, len, 0);
        }
        close(sockfd);

    }
    return 0;
}
