#include "udp_client.h"
#include "tcp_client.h"

#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

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
    char *address ;

    while ((res = getopt(argc,argv,"utp:a:")) != -1)
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
            case 'a':
                address = optarg;
                break;
            case 'h':
            default:
                usage();
                break;
        }
    }
    if (protocol == UDP)
    {
        int sockfd = create_udp_socket();
        struct sockaddr_in serv = configure_udp_client(port, address);
        run_udp_client(sockfd, &serv);
    }
    else if (protocol == TCP)
    {
        int sockfd = configure_tcp_client(port, address);
        run_tcp_client(sockfd);
    }

    return 0;
}
