#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<string.h>

struct stu{
    int id;
    char name[20];
};

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    struct stu s1={1,"xiaoming"};
    int fd;
    char *p=NULL;

    fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0664);
    ftruncate(fd,sizeof(s1));
    p=mmap(NULL,sizeof(s1),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    if(p==MAP_FAILED){
        sys_err("mmap error");
    }
    close(fd);
    printf("start write\n");
    while(1){
        memcpy(p,&s1,sizeof(s1));
        printf("succed write %d\n",s1.id);
        s1.id++;
        sleep(1);
    }
    munmap(p,sizeof(s1));
    return 0;


}