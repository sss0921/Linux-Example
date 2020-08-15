#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>

#define PORT 8888

extern void sig_process(int signo);
extern void sig_pipe(int sign);
static struct iovec *vs = NULL, *vc = NULL;

void process_conn_client(int s)
{
	char buffer[30];
	ssize_t size = 0;

	struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));
	if(!v) {
		printf("Not enough memory\n");
		return;
	}

	vc = v;

	v[0].iov_base = buffer;
	v[1].iov_base = buffer + 10;
	v[2].iov_base = buffer + 20;

	v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;

	for(;;) {
		size = read(0, v[0].iov_base, 10);
		printf("%d ----", size);
		if(size < 0)
			continue;

		writev(s, v, 1);
		v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;
		size = readv(s, v, 3);
		for(int i = 0; i < 3; i++) {
			if(v[i].iov_len > 0) {
				write(1, v[i].iov_base, v[i].iov_len);
			}
		}
	}
}

void sig_process(int signo)
{
	printf("Catch a exit signal\n");
	free(vc);
	free(vs);
	exit(0);
}

void sig_pipe(int sign)
{
	printf("Catch a SIGPIPE signal\n");
	free(vc);
	free(vs);
	exit(0);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr;
	
	if(argc == 1) {
		printf("PLS input server addr\n");
	}

	signal(SIGINT, sig_process);
	signal(SIGPIPE, sig_pipe);
	
    int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0) {
		printf("socket error\n");
		return -1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

	connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	process_conn_client(s);

	return 0;
}
