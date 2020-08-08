#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct in_addr ip;

	char *str1 = NULL;
	char *str2 = NULL;

	ip.s_addr = 127<<24|0<<16|0<<8|1;
	str1 = inet_ntoa(ip);
	ip.s_addr = 255<<24|255<<16|255<8|255;
	str2 = inet_ntoa(ip);
	printf("inet_ntoa:\tip1:0x%xstring1:%s\tip2:0x%xstring2:%s\n",ip.s_addr,str1, ip.s_addr, str2);

	return 0;
}
