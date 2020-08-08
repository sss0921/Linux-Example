#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

int issockettype(int fd)
{
	struct stat st;

	int err = fstat(fd, &st);

	if(err < 0) {
		return -1;
	}

	if((st.st_mode & S_IFMT) == S_IFSOCK) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char *argv[])
{
	int ret = issockettype(0);
	printf("value %d\n", ret);
	
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	ret = issockettype(fd);
	printf("value %d\n", ret);

	return 0;
}
