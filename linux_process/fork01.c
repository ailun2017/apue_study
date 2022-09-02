#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = 0;
	printf("[%d]begin",getpid());
	fflush(NULL);//fork之前一定记得刷新全部缓冲区，不然会打印两次begin
	pid = fork();
	if (pid < 0)
	{
		printf("fork() error!\n");
	}

	if (0 == pid)
	{
		printf("[%d]child process into\n",getpid());
	}
	else
	{
		printf("[%d]parnet process into\n",getpid());
	}
	printf("[%d]end",getpid());
	return 0;
}
