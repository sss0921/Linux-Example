#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct in_addr ip,network;
	char addr[] = "255.255.255.1";

	inet_aton(addr, &ip);
	network.s_addr = inet_netof(ip);
	printf("inet_netof:string %s ip:0x%x \n",addr, network.s_addr);
	return 0;
}
