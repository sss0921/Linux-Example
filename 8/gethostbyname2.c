#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char host1[] = "www.sohu.com";
	char host2[] = "www.sina.com.cn";

	struct hostent *ht1 = NULL;
	struct hostent *ht2 = NULL;

	char str[30];
	ht1 = gethostbyname(host1);
	ht2 = gethostbyname(host2);
	for(int j = 0; j < 2; j++) {
		struct hostent *ht = NULL;
		char *host = NULL;
		if(j == 0) {
			ht = ht1;
			host = host1;
		} else {
			ht = ht2;	
			host = host2;	
		}
		printf("get the host:%s addr\n",host);
		printf("name:%s\n",ht->h_name);
		printf("types:%s\n",ht->h_addrtype==AF_INET?"AF_INET":"AF_INET6");
		printf("length:%d\n",ht->h_length);
		/*打印IP地址*/
		for(int i = 0;;i++) {
			if(ht->h_addr_list[i] != NULL) {
				printf("IP:%s\n",inet_ntop(ht->h_addrtype, ht->h_addr_list[i], str, 30));
			} else {
				break;
			}
		}
		/*打印域名地址*/
		for(int i = 0;;i++) {
			if(ht->h_aliases[i] != NULL) {
				printf("alias %d:%s\n",i,ht->h_aliases[i]);
			} else {
				break;
			}
		}
	}

	return 0;
}
