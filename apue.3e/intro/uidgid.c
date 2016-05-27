#include "apue.h"

int
main(void)
{
	printf("uid = %d, gid = %d pid = %ld \n", getuid(), getgid(),(long)getpid());
	exit(0);
}
