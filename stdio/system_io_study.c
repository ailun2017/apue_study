#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


void compare_sysio_and_stdio()
{
	putchar('a');
	write(1, "b", 1);
    putchar('a');
    write(1, "b", 1);
}

#define BUFFSIZE 1024*1000*2
char buf[BUFFSIZE];

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
		//printf("len = %d\n", len);
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
			//printf("ret = %d\n", ret);
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

void delete_line(char* filename , int linenum)
{
	int rd_fd, wr_fd;
	char buff[BUFFSIZE];
	memset(buff, '\0', sizeof(buff));
	int count = 0;
	int len = 0;
	int pos = 0;
	int ret = 0;
	int len_before_linenum = 0;
	rd_fd = open(filename, O_RDONLY);
	if (rd_fd < 0)
	{
		perror("open()");
		return;
	}
	len_before_linenum = 1;
	count = 0;
	while(1)
	{
		if (count < linenum)
		{
			len = read(rd_fd, buff, 1);
			if (len < 0)
			{
				perror("read()");
				break;
			}
			if (0 == len)
			{
				printf("len == 0\n");
				break;
			}
		
			if ('\n' == buff[0])
			{
				count++;
			}
			if (count < (linenum-1))
			{
				len_before_linenum++;
			}
		}
		else
		{
			len = read(rd_fd, buff+pos, 1);			
            if (len < 0)
            {
                perror("read()");
                break;
            }
            if (0 == len)
            {
                printf("len == 0\n");
                break;
            }
			pos++;
		}
	}
	//printf("buf: %s", buff);
	wr_fd = open(filename, O_WRONLY);
	if (wr_fd < 0)
	{
		perror("open()");
		close(rd_fd);
		return;
	}
	ftruncate(wr_fd, len_before_linenum+1);
	//printf("after trunc: %s", buff);
	printf("len_before_linenum %d, pos %d\n", len_before_linenum, pos);
	lseek(wr_fd, len_before_linenum, SEEK_SET);
	len = pos + 1;
	pos = 0;
	while(len > 0)
	{
		ret = write(wr_fd, buff+pos, len);

		if (ret < 0)
		{
			perror("write()");
			break;
		}
		printf("ret %d\n", ret);
		len -= ret;
		pos += ret;
	}

	close(rd_fd);
	close(wr_fd);
}

int main(int argc, char* argv[])
{
	if (0)
	{
		compare_sysio_and_stdio();
	}
	if (0)
	{
		my_copy(argc, argv);
	}
	if (1)
	{
		if (argc < 2)
		{
			printf("usage...\n");
			exit(-1);
		}
		delete_line(argv[1], 3);
	}
	exit(0);
}
