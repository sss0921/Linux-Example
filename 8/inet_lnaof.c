#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct in_addr ip,local,network;
	char addr[] = "127.0.0.1";

	inet_aton(addr, &ip);
	local.s_addr = inet_lnaof(ip);
	printf("inet_lanof:string %s ip:0x%x \n",addr, local.s_addr);
	return 0;
}
