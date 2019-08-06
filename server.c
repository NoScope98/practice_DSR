#include "udp_server.h"
#include "tcp_server.h"

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

enum Protocol
{
    UDP = 1,
    TCP
};

void usage()
{
    printf("Usage -u for UDP, -t for TCP, -p <PORT> for port, -a <ADDRESS> for address\n");
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage();
        exit(0);
    }

    int res = 0;
    int port = 0;
    enum Protocol protocol;

    while ((res = getopt(argc,argv,"utp:")) != -1)
    {
	switch (res)
        {
            case 'u':
                protocol = UDP;
                break;
            case 't':
                protocol = TCP;
                break;
            case 'p':
                port = atoi(optarg);
                if (port == 0)
                {
                    printf("Port shouldn't be null\n");
                    exit(0);
                }
                break;
            case 'h':
            default:
                usage();
                break;
        }
    }
    if (protocol == UDP)
    {
        int sockfd = configure_udp_server(port);
        run_udp_server(sockfd);
    }
    else if (protocol == TCP)
    {
        int listener = configure_tcp_server(port);
        run_tcp_server(listener);
    }
    return 0;
}
