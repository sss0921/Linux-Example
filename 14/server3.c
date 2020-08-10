#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define BUFFLEN 1024
#define SERVER_PORT 8888
#define BACKLOG 5
#define PIDNUM 2

static void handle_connect(int s)
{
	struct sockaddr_in from;
	socklen_t len = sizeof(from);
	char buff[BUFFLEN];

	while(1) {
		memset(buff, 0, BUFFLEN);
		int n = recvfrom(s, buff, BUFFLEN, 0, (struct sockaddr*)&from, &len);
		if(n > 0 && !strncmp(buff, "TIME", 4)) {
			memset(buff, 0, BUFFLEN);
			time_t now = time(NULL);
			sprintf(buff, "%24s\r\n", ctime(&now));
			sendto(s, buff, strlen(buff), 0, (struct sockaddr*)&from, len);
		}
	}
}

void sig_int(int num)
{
	exit(1);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in local;
	int s_s = socket(AF_INET, SOCK_DGRAM, 0);

	signal(SIGINT, sig_int);

	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(SERVER_PORT);

	bind(s_s, (struct sockaddr*)&local, sizeof(local));

	pid_t pid[PIDNUM];

	for(int i = 0; i < PIDNUM; i++) {
		pid[i] = fork();
		if(pid[i] == 0) {
			handle_connect(s_s);		
		}
	}

	while(1);
	return 0;
}
