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

void *tfn(void *arg)
{
    int i=(int)arg;  //因为参数arg是void*类型的，需要强转成int类型
    printf("I am %d thread, my thread id is%lu\n",i+1,pthread_self());
    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret;
    int i;
    for(i=0;i<5;i++)
    {
        ret=pthread_create(&thread_id,NULL,tfn,(void *)i);  //将i作为传入参数传入tfn回调函数中，注意类型，所以需要强制转换
        if (ret!=0){
            sys_err("pthread creat error");
        }
    }
    sleep(i);
    printf("I am main,thread id is %lu\n",pthread_self());
    return 0;
}