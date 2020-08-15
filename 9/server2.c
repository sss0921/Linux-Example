#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 8888
#define BACKLOG 2

static struct iovec *vs = NULL, *vc = NULL;

void sig_process(int signo)
{
	printf("Catch a exit signal\n");
	free(vc);
	free(vs);
	exit(0);
}

void process_conn_server(int s)
{
	char buffer[30];
	ssize_t size = 0;

	struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));

	if(!v) {
		printf("Not enough memory\n");
		return;
	}	

	vs = v;

	v[0].iov_base = buffer;
	v[1].iov_base = buffer + 10;
	v[2].iov_base = buffer + 20;
	v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;

	for(;;) {
		size = readv(s, v, 3);

		if(size == 0)
			return;

		sprintf(v[0].iov_base, "%ld ", size);
		sprintf(v[1].iov_base, "bytes alt");
		sprintf(v[2].iov_base, "ogether\n");

		v[0].iov_len = strlen(v[0].iov_base);
		v[1].iov_len = strlen(v[1].iov_base);
		v[1].iov_len = strlen(v[2].iov_base);

		writev(s, v, 3);
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	signal(SIGINT, sig_process);
	signal(SIGPIPE, sig_process);

	int ss = socket(AF_INET, SOCK_STREAM, 0);

	if(ss < 0) {
		printf("socket error\n");
		return -1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	int err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(err < 0) {
		printf("bind error\n");
		return -1;
	}

	err = listen(ss, BACKLOG);
	if(err < 0) {
		printf("listen error\n");
		return -1;
	}

	for(;;) {
		int addrlen = sizeof(struct sockaddr);
		int sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
		if(sc < 0) {
			printf("accpet error\n");
			continue;
		}

		pid_t pid = fork();
		if(pid == 0) {
			close(ss);
			process_conn_server(sc);
		} else {
			close(sc);
		}
	}
}
