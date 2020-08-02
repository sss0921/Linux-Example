#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid, ppid;

	pid = getpid();
	ppid = getppid();

	printf("当前进程的ID为: %d\n",pid);
	printf("当前进程的父进程ID为: %d\n",ppid);

	return 0;
}
