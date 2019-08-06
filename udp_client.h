#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

int create_udp_socket();
struct sockaddr_in configure_udp_client(int port, char *address);
void run_udp_client(int sockfd, struct sockaddr_in *serv);

#endif /*UDP_CLIENT_H*/
