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
    //sleep(3),sleep相当于一个系统调用，如果可以作为cancel的取消点，如果没有sleep的话需要pthread_testcancel手动添加取消点
    pthread_testcancel();  //为什么在打印之前就已经设置了取消点，打印还是能正常打印呢，初步怀疑是因为线程执行的比较快，主线程还没执行到cancel函数，而线程已经执行完printf函数了
    printf("my thread id is%lu\n",pthread_self());
    
    
    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret;
    ret=pthread_create(&thread_id,NULL,tfn,NULL);  //将i作为传入参数传入tfn回调函数中，注意类型，所以需要强制转换
    if (ret!=0){
        sys_err("pthread creat error");
    }
    
    //sleep(5);
    pthread_cancel(thread_id);
    ret=pthread_join(thread_id,NULL);
    if(ret!=0)
    {
        fprintf(stderr,"join error:%s\n",strerror(ret));
    }
    printf("I am main,thread id is %lu\n",pthread_self());
    while(1);
    pthread_exit(NULL);
}