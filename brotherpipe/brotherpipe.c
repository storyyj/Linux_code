#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int fd[2];
    pid_t pid,tmpid1,tmpid2;
    int ret,i;
    int status1,status2;

    ret=pipe(fd);
    if(ret==-1)
    {
        sys_err("pipe error");
    }

    for(i=0;i<2;i++)
    {
        pid=fork();
        if(pid==0){
            break;
        }
        if(pid>0||i==0){
            tmpid1=pid;
            printf("big brother is %d\n",tmpid1);
        }
        if(pid>0||i==1){
            tmpid2=pid;
            printf("little brother is %d\n",tmpid2);
        } 

    }
    if(i==2)  //父进程，不参与管道的使用，所以要关掉读写管道并且wait()子进程
    {
        close(fd[0]);
        close(fd[1]);
        waitpid(tmpid1,&status1,WNOHANG);
        waitpid(tmpid2,&status2,0);
    }
    if(i==0)  //兄进程，因为上面的for循环i=0时兄进程直接break了，就继续执行for循环下面的代码，且只有i=0的第一次fork的进程能进到这个语句块内,兄进程写
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        sleep(5);
        execlp("ls","ls",NULL);
        sys_err("execlp write error");
    }
    if(i==1)  //弟弟进程，将标准输入设备重定向到管道的读端
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l", NULL);
        sys_err("execlp read error");
    }
    return 0;
}