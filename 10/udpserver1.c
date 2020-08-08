#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT_SERV 8888
#define BUFF_LEN 256

void static udpserver_echo(int s, struct sockaddr *client)
{
	int n;
	char buff[BUFF_LEN];
	socklen_t len;
	while(1) {
		len = sizeof(*client);
		n = recvfrom(s, buff, BUFF_LEN, 0, client, &len);
		sendto(s, buff, n, 0, client, len);
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in addr_server, addr_client;
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&addr_server, 0, sizeof(addr_server));
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(PORT_SERV);

	bind(s, (struct sockaddr*)&addr_server, sizeof(addr_server));
	
	udpserver_echo(s, (struct sockaddr*)&addr_client);

	return 0;
}
