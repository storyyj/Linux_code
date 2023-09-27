#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex1,mutex2;
int var1=1;
int var2=2;

void *tfn(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        //pthread_mutex_lock(&mutex);  //造成死锁的原因之一，反复上锁，在一个线程内对于一把锁上了两次
        printf("hello %d",var1);
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex1);
        sleep(1);
    }

    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_create(&tid,NULL,tfn,NULL);
    while(1)
    {
        /*造成死锁的条件2：两个线程各自持有一把锁，请求另一把
        但是我给主线程加了一个sleep，子线程应该已经都获得了两把锁才对
        为什么这样子运行还是会阻塞呢*/
        sleep(1);          
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);
        printf("HELLO %d",var2);
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
        sleep(1);
    }
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    
    return 0;


}