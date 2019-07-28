#include "udp_client.h"
#include "tcp_client.h"

#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
        printf("Usage -u for UDP, -t for TCP, -p for port, -a for address\n");

    int res = 0;
    int port = 0;
    int protocol = 0;
    char *address ;

    while ((res = getopt(argc,argv,"utp:a:")) != -1)
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
            case 'a':
                address = optarg;
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
        int sockfd = sock();
        struct sockaddr_in serv = configure(port, address);
        run(sockfd, &serv);
    }
    else if (protocol == 2) // TCP
    {
        int sockfd = configure_tcp_client(port, address);
        run_tcp_client(sockfd);
    }

    return 0;
}
