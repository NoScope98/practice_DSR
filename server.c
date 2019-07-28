#include "udp_server.h"
#include "tcp_server.h"

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
        printf("Usage -u for UDP, -t for TCP, -p for port\n");

    int res = 0;
    int port = 0;
    int protocol = 0;

    while ((res = getopt(argc,argv,"utp:")) != -1)
    {
	switch (res)
        {
            case 'u':
                protocol = 1;
                break;
            case 't':
                protocol = 2;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case '?':
                printf("\nUsage -u for UDP, -t for TCP, -p for port\n");
                break;
            default:
                printf("\nUsage -u for UDP, -t for TCP, -p for port\n");
                break;
        }
    }
    if (protocol == 1) // UDP
    {
        int sockfd = configure(port);
        run(sockfd);
    }
    else if (protocol == 2) // TCP
    {
        int listener = configure_tcp_server(port);
        run_tcp_server(listener);
    }
    return 0;
}
