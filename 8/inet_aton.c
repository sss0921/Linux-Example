#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct in_addr ip;
	char addr1[] = "127.0.0.1";
	int err = 0;
	err = inet_aton(addr1, &ip);
	if(err) {
		printf("inet_aton:string %s value is:0x%x\n",addr1, ip.s_addr);
	} else {
		printf("inet_aton:string %s error\n",addr1);
	}
	return 0;
}
