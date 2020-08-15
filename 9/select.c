#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	fd_set rd;
	struct timeval tv;
	
	FD_ZERO(&rd);
	FD_SET(0, &rd);

	tv.tv_sec = 5;
	tv.tv_usec = 0;

	int err = select(1, &rd, NULL, NULL, NULL);

	if(err == -1)
		perror("select()");
	else if(err)
		printf("Data is available now.\n");
	else
		printf("No Data within five seconds.\n");

	return 0;
}
