SRCSERV = server.c udp_server.c tcp_server.c
OBJSERV = $(SRCSERV:.c=.o)

SRCCLI = client.c udp_client.c tcp_client.c
OBJCLI = $(SRCCLI:.c=.o)

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

udp_server.o: udp_server.c
	gcc -c -o udp_server.o udp_server.c
tcp_server.o: tcp_server.c
	gcc -c -o tcp_server.o tcp_server.c
server.o: server.c
	gcc -c -o server.o server.c
$(SERVER): $(OBJSERV)
	gcc $(OBJSERV) -o $(SERVER)

udp_client.o: udp_client.c
	gcc -c -o udp_client.o udp_client.c
tcp_client.o: tcp_client.c
	gcc -c -o tcp_client.o tcp_client.c
client.o: client.c
	gcc -c -o client.o client.c
$(CLIENT): $(OBJCLI)
	gcc $(OBJCLI) -o $(CLIENT)

clean:
	rm -rf $(SERVER) $(CLIENT) $(OBJSERV) $(OBJCLI)
