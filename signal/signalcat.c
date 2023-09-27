#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void sig_catch(int signo)
{
    printf("catch you!!! %d\n",signo);
    return;
}
int main(int argc,char *argv[])
{
    signal(SIGINT,sig_catch);  //由signal函数注册信号捕捉函数，由内核捕捉SIGINT信号
    signal(SIGQUIT,sig_catch);
    signal(SIGBUS,sig_catch);
    while(1);
    return 0;
}