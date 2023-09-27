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
    struct stu s1;
    int fd,ret;
    struct stu *student=NULL;

    fd=open(argv[1],O_RDWR);  //fd=open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0664);如果这么写就是错的，因为O_TRUNC是将文件清零，会BUS ERROR
    student=mmap(NULL,sizeof(s1),PROT_READ,MAP_SHARED,fd,0);
    close(fd);
    if(student==MAP_FAILED){
        sys_err("mmap error");
    }
    while(1){
        printf("student id is%d,name is %s\n",student->id,student->name);
        sleep(1);
    }
    munmap(student,sizeof(s1));
    return 0;


}