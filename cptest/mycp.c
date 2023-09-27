#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
	char buf[1024];

	int n=0;
	int fd1=open(argv[1], O_RDONLY);
	int fd2=open(argv[2], O_RDWR|O_CREAT|O_TRUNC,0664);

	while((n=read(fd1, buf, 1024))!=0){
		printf("read %d byte", n);
		write(fd2, buf, n);
	}
	close(fd1);
	close(fd2);

	return 0;
}
