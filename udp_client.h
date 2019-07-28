#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

int sock();
struct sockaddr_in configure(int port, char *address);
void run(int sockfd, struct sockaddr_in *serv);

#endif /*UDP_CLIENT_H*/
