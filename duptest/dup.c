#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	int fd = open(argv[1], O_RDWR);
	int newfd = dup(fd);
	printf("newfd is%d",newfd);
	int ret = write(newfd,"you are a sb\n",12);
	return 0;
}
