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
    sleep(5);
    printf("really catch you!!! %d\n",signo);
    return;
}
int main(int argc,char *argv[])
{
    struct sigaction act,old_act;  //初始化两个sigaction结构体用于传入sigaction函数，sigaction结构体中包含前面的信号集sig_set的set结构体作为sa_mask
    act.sa_handler=sig_catch;  //设置act结构体中的回调函数
    sigemptyset(&(act.sa_mask));  //清空sa_mask中的屏蔽字，这个set只在回调函数sig_catch工作时有效，即如果想在捕捉函数工作时屏蔽其他的信号设置这个set即可
    sigaddset(&act.sa_mask,SIGQUIT);  //在捕捉函数执行期间，设置屏蔽SIGQUIT信号，该信号会等捕捉函数执行结束了再被执行。
    act.sa_flags=0;  //默认值为0，表示在捕捉函数执行期间。本信号会自动屏蔽，等捕捉函数执行结束再执行一次本信号
    int ret = sigaction(SIGINT,&act,&old_act);
    while(1);
    return 0;


}