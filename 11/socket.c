#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

/*
 * 错误处理函数
 */

static void display_error(const char *on_what)
{
	perror(on_what);
	exit(1);
}

int main(int argc, char *argv[])
{
	int error = -1;
	int s = -1;
	struct sockaddr_un addr_unix;
	int len_unix = 0;
	const char path[] = "/demo/path";
	
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if(s == -1) 
		display_error("socket()");	

	unlink(path);

	memset(&addr_unix, 0, sizeof(addr_unix));

	addr_unix.sun_family = AF_LOCAL;
	strcpy(addr_unix.sun_path, path);
	addr_unix.sun_path[0] = 0;
	len_unix = SUN_LEN(&addr_unix);

	error = bind(s, (struct sockaddr*)&addr_unix, len_unix);

	if(error == -1)
		display_error("bind()");
	
	close(s);
	unlink(path);
	
	return 0;
}
