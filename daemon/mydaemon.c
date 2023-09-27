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
/*父进程创建子进程后，父进程退出后，子进程成为孤儿进程由init进程收养，其父进程的id会变为init进程的pid，
但其组进程id pgid并不会改变，还是创建他的那个父进程的组id，只不过这个进程组没有组长了*/
int main(int argc,char *argv[])
{
    pid_t pid;
    pid=fork();
    if(pid>0)
    {   
        printf("I am parent,my id is %d,my pgid is %d\n",getpid(),__getpgid(0));
        sleep(5);
        exit(1);
    }
    else
    {
        while(1){
            printf("I am child,my id is %d,my pgid is %d, my parent id is %d\n",getpid(),__getpgid(0),getppid());
            sleep(1);
        }
    }
}