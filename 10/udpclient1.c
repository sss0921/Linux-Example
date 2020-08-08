#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT_SERV 8888
#define BUFF_LEN 256

void static udpclient_echo(int s, struct sockaddr *to)
{
	char buff[BUFF_LEN] = "UDP TEST";

	struct sockaddr_in from;
	socklen_t len = sizeof(*to);
	sendto(s, buff, BUFF_LEN, 0, to, len);
	recvfrom(s, buff, BUFF_LEN, 0, (struct sockaddr*)&from, &len);
	printf("recved:%s\n", buff);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in addr_server;
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&addr_server, 0, sizeof(addr_server));
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(PORT_SERV);
	
	udpclient_echo(s, (struct sockaddr*)&addr_server);

	close(s);
	return 0;
}
