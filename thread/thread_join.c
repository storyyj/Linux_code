#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

struct thrd{
    int var;
    char str[256];
};

void *tfn(void *arg)
{
    int i=(int)arg;
    struct thrd *tval;  //创造一个指向thrd结构体的指针，然后往该指针所指向的结构体中赋值，最后将该指针return回去给join接收
    tval=malloc(sizeof(tval));
    tval->var=i+1;
    strcpy(tval->str,"Hello thread!");  //想要往thrd结构体的str赋值只能调用strcpy函数，不能直接用等号=赋值
    printf("I am %d thread, my thread id is%lu\n",i+1,pthread_self());
    return (void *)tval;  //因为该回调函数的返回值是void*类型，所以return回去的tval指针需要做类型的强制转换
}
int main(int argc,char *argv[])
{
    pthread_t thread_id[5];
    int ret;
    int i;
    struct thrd *retval;
    for(i=0;i<5;i++)
    {
        ret=pthread_create(&thread_id[i],NULL,tfn,(void*)i);  //因为需要用join循环回收子线程，join回收子线程需要指定线程id，所以使用数组来存放每一个线程id
        if (ret!=0){
            sys_err("pthread creat error");
        }
        sleep(1);
        pthread_join(thread_id[i],(void **)&retval);
        printf("I am %dth thread,I success be wait,%s\n",retval->var,retval->str);  //这里是创建一个线程运行结束后直接回收，如果是要等所有线程都运行完之后再循环回收除了需要另外再写一个循环之外，还需要一个retval[5]数组存放五个线程的返回值
    }
    sleep(i);
    printf("I am main,thread id is %lu\n",pthread_self());
    return 0;
}