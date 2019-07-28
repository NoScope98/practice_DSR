#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

int configure_tcp_client(int port, char *address);
void run_tcp_client(int sockfd);

#endif /*TCP_CLIENT_H*/
