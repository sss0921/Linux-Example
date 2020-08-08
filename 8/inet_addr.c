#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, int *argv[])
{
	struct in_addr ip;
	char addr1[] = "127.0.0.1";
	char addr2[] = "255.255.255.255";
	ip.s_addr = inet_addr(addr1);
	if(ip.s_addr != -1) {
		printf("inet_addr:string %s vlaue is:0x%x\n", addr1, ip.s_addr);
	} else {
		printf("inet_addr:string %s\n", addr1);
	}
	ip.s_addr = inet_addr(addr2);
	if(ip.s_addr != -1) {
		printf("inet_addr:string %s value is:0x%x\n", addr2, ip.s_addr);
	} else {
		printf("inet_addr:string %s\n", addr2);
	}
	return 0;
}
