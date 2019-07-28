#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define BUF_LEN 1500

int configure_tcp_server(int port)
{
    int listener;
    struct sockaddr_in servaddr;

    if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error creating socket\n");
        exit(0);
    }

    printf("Socket has been creating\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket\n");
        exit(0);
    }
    printf("Socket has bound\n");

    return listener;
}

void run_tcp_server(int listener)
{
    char buf[BUF_LEN];

    int sockfd;
    int len;

    listen(listener, 1);

    while (1)
    {
        if ((sockfd = accept(listener, NULL, NULL)) < 0)
        {
            perror("Error accept");
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
}

/*
int main(int argc, char *argv[])
{
    int listener = configure(55555);
    run(listener);
    return 0;
}
*/
