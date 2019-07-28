#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define ADDRESS "127.0.0.1"
#define BUF_LEN 1500

int sock()
{
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error creating socket\n");
        exit(0);
    }
    printf("Socket has been created\n");

    return sockfd;
}

struct sockaddr_in configure(int port, char *address)
{
    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = inet_addr(address);

    return serv;
}

void run(int sockfd, struct sockaddr_in *serv)
{
    char buf[BUF_LEN];
    int len;

    struct sockaddr_in cliaddr;

    while (1)
    {
        printf("Enter the message: ");
        fgets(buf, sizeof(buf), stdin);

        len = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)serv, sizeof(*serv));

        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);

        buf[len] = '\0';
	printf("Recieved: '%s'\n", buf);
    }

    close(sockfd);
}

/*
int main(int argc, char *argv[])
{
    int sockfd = sock();
    struct sockaddr_in serv = configure(55555, "127.0.0.1");
    run(sockfd, &serv);
    return 0;
}
*/
