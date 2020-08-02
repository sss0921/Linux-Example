#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int result = -1;
	int fd[2];
	int nbytes = -1;
	pid_t pid;

	char string[] = "你好,管道!";
	char readbuf[80];

	int *write_fd = &fd[1];
	int *read_fd = &fd[0];

	result = pipe(fd);

	if(-1 == result) {
		printf("建立管道失败\n");
		return -1;
	}

	pid = fork();

	if(0 == pid) {
		close(*read_fd);
		result = write(*write_fd, string, strlen(string));
	} else {
		close(*write_fd);
		nbytes = read(*read_fd, readbuf, sizeof(readbuf));
		printf("接收到%d个数据,内容为:%s\n",nbytes,readbuf);
	}

	return 0;
}
