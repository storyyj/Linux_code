#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void sig_catch(int signo)
{   
    pid_t wpid;	
    int status;
    while((wpid=waitpid(-1,&status,0))!=-1)
    {	    
    printf("catch child  %d\n",wpid);
    }
    return;
}
int main(int argc,char *argv[])
{
    /*要想避免子进程在父进程注册捕捉函数之前变成僵尸进程，可以在这个地方设置信号屏蔽字
    等注册完捕捉函数之后再解除信号屏蔽字*/
    sigset_t set,old_set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);
    sigprocmask(SIG_BLOCK,&set,&old_set);  //设置屏蔽SIGCHLD信号，等解除屏蔽后父进程再批量处理

    int i;
    pid_t pid;
    for(i=0;i<7;i++)
    {
	    if((pid=fork())==0)
	    {
		    break;
	    }
    }
    if(i==7)
    {
        struct sigaction act,old_act;  //初始化两个sigaction结构体用于传入sigaction函数，sigaction结构体中包含前面的信号集sig_set的set结构体作为sa_mask
        act.sa_handler=sig_catch;  //设置act结构体中的回调函数
        sigemptyset(&(act.sa_mask));  //清空sa_mask中的屏蔽字，这个set只在回调函数sig_catch工作时有效，即如果想在捕捉函数工作时屏蔽其他的信号设置这个set即可
        act.sa_flags=0;  //默认值为0，表示在捕捉函数执行期间。本信号会自动屏蔽，等捕捉函数执行结束再执行一次本信号
        sleep(3);  //如果在这里加一个延时，模仿父进程还没注册捕捉函数之前子进程就已经死亡，父进程因为没来得及收到子进程状态变化发送的SIGCHLD信号而导致七个子进程全部变为僵尸进程
        int ret = sigaction(SIGCHLD,&act,&old_act);  //注册SIGCHLD信号的捕捉函数
        sigprocmask(SIG_UNBLOCK,&set,&old_set);
        printf("I am parent %d\n",getpid());
        while(1);

    }
    else{
        printf("I am childre %d\n",getpid());
        return i;
    }

    return 0;


}
