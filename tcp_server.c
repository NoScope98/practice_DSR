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
    int len;
    int i;
    int j;

    fd_set active_fds;
    fd_set read_fds;
    int fdmax;

    int newfd;

    listen(listener, 10);

    FD_ZERO (&active_fds);
    FD_SET(listener, &active_fds);
    fdmax = listener;

    while (1)
    {
        read_fds = active_fds;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) < 0)
        {
            perror("Error select\n");
            exit(0);
        }
        for (i = 0; i <=fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == listener)
                {
                    if ((newfd = accept(listener, NULL, NULL)) < 0)
                    {
                        perror("Error accept\n");
                        exit(0);
                    }
                    else
                    {
                        FD_SET(newfd, &active_fds);
                        if (newfd > fdmax)
                        {
                            fdmax = newfd;
                        }
                        printf("New connection!\n");
                    }
                }
                else
                {
                    if (len = recv(i, buf, sizeof(buf), 0) <= 0)
                    {
                        //perror("Error recv\n");
                        close(i);
                        FD_CLR(i, &active_fds);
                    }
                    else
                    {
                        printf("Received: '%s' from client\n", buf);
                        send (i, buf, len, 0);
                    }
                }
            }
        }
    }
}
