#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int fd1=open("out.txt", O_RDWR);
	int ret=dup2(fd1,STDOUT_FILENO);
	execlp("ps", "ps","aux",NULL);
	close(fd1);
	return 0;
}
