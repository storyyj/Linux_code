#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/mman.h>
#include<stdlib.h>
void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int fd;
    int ret;
    char *p=NULL;

    fd=open("test.txt",O_RDWR);
    if(fd==-1){
        sys_err("open error");
    }
    
    lseek(fd,10,SEEK_END);  //扩展文件大小，因为若源文件的大小为0，创建mmap内存映射区会出错
    write(fd,"\0",1);  //lseek函数只是移动光标而已，需要加一个write才能扩展实际的文件大小，引起IO操作

    int len=lseek(fd,0,SEEK_END);
    p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);  //第一个参数的意思是指定内存区的地址，若传入NULL则是让操作系统自动帮你分配
    close(fd);
    if(p==MAP_FAILED)
    {
        sys_err("mmap error");
    }
    strcpy(p,"hello2222 mmap\n");
    printf("------%s\n",p);
    ret=munmap(p,len);
    if(ret==-1){
        sys_err("munmap error");
    }
    return 0;
    
}
