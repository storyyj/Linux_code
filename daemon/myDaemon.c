#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int ret,fd;
    pid_t pid;
    pid=fork();
    if(pid>0)
    {
        exit(0);
    }
    setsid();  //设置会话id后应该就已经脱离了终端了
    chdir("/");
    umask(0022);
    close(STDIN_FILENO);
    fd=open("dev/null",O_RDWR);
    printf("mini fd is %d",fd);  //所以这一步想要在屏幕上打印出来当前最小的fd就打印不出来，此时的fd应该是0，因为关闭了标准输入0，再打开一个文件给他分配的文件描述符会从最小的开始，也就是0
    dup2(fd,STDERR_FILENO);
    dup2(fd,STDERR_FILENO);
    while(1);
    return 0;

}