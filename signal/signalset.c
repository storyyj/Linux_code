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

void print_set(sigset_t *set)
{
    for(int i=1;i<32;i++)
    {
        if(sigismember(set,i))  //判断一个信号是否在集合中，即判断该信号是否被屏蔽了，若被屏蔽返回1，若没被屏蔽，返回0
        {
            putchar('1');
        }
        else{
            putchar('0');
        }
    }
    printf("\n");
}
int main(int argc,char *argv[])
{
    int ret=0;
    sigset_t set,old_set,pd_set;  //一共32位常用信号，bitmap
    sigemptyset(&set);  //初始化自定义信号集set，将全部位置0
    sigemptyset(&old_set);
    sigemptyset(&pd_set);
    sigaddset(&set,SIGINT);  //添加要屏蔽的信号，本质上是将其置1
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGBUS);

    ret=sigprocmask(SIG_BLOCK,&set,&old_set);  //设置阻塞，将自定义set与内核的信号屏蔽字set取或，即设置信号屏蔽字
    sigprocmask(SIG_UNBLOCK,&set,&old_set);  //取消阻塞，将自定义set取反，再与信号屏蔽字set取与。即可取消刚刚设置的阻塞
    if(ret==-1)
    {
        sys_err("set error");
    }
    
    while(1)
    {
        ret=sigpending(&pd_set);  //查看内核自带的未决信号集,这一步要放在while循环中，这样才能及时更新未决信号集
        print_set(&pd_set);
        sleep(1);
    }
    return 0;

}