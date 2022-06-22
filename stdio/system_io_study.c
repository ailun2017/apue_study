#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


void compare_sysio_and_stdio()
{
	putchar('a');
	write(1, "b", 1);
    putchar('a');
    write(1, "b", 1);
}

#define BUFFSIZE 1024
void my_copy(int argc, char* argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "argc is < 3!\n");
		return;
	}

	int sfd, dfd;
	int len;
	int ret;
	int pos;
	char buf[BUFFSIZE];

	sfd = open(argv[1], O_RDONLY);
	if (sfd < 0)
	{
		perror("open()");
		return;
	}
	printf("sfd %d, argv[1] %s\n", sfd, argv[1]);

	dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (dfd < 0)
	{
		close(sfd);
		perror("open()");
		return;
	}
	printf("dfd %d \n", dfd);
	ret = lseek(sfd, 0, SEEK_SET);
	if (ret < 0)
	{
		perror("lseek()");
	}

	while(1)
	{
		len = read(sfd, (void*)&buf[0], BUFFSIZE);
		printf("len = %d\n", len);
		if (len < 0)
		{
			perror("read()");
			break;
		}
		if (0 == len)
		{
			printf("len is 0!\n");
			break;
		}
		pos = 0;
		while(len > 0)
		{
			ret = write(dfd, buf + pos, len);
			printf("ret = %d\n", ret);
			if (ret < 0)
			{
				perror("write()");
				close(sfd);
    			close(dfd);
				return;
			}
			len -= ret;
			pos += ret;
		}
	}
	close(sfd);
	close(dfd);
}

int main(int argc, char* argv[])
{
	compare_sysio_and_stdio();
	my_copy(argc, argv);
	exit(0);
}
