#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFLEN 1024
#define SERVER_PORT 8888

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	char buff[BUFFLEN];
	int n = 0;

	int s = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_PORT);

	memset(buff, 0, BUFFLEN);
	strcpy(buff, "TIME");

	sendto(s, buff, strlen(buff), 0, (struct sockaddr*)&server, sizeof(server));

	memset(buff, 0, BUFFLEN);

	socklen_t len = sizeof(server);
	n = recvfrom(s, buff, BUFFLEN, 0, (struct sockaddr *)&server, &len);
	
	if(n > 0)
		printf("TIME:%s", buff);

	close(s);
	return 0;
}
