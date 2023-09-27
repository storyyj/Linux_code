#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDWR);
	if(fd == -1){
		perror("open error");
		exit(1);
	}
	int length = lseek(fd, -1, SEEK_SET);
	printf("file size: %d\n",length);
	close(fd);
	return 0;
}
