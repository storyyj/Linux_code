#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void err_thread(int ret,char *str)
{
    if(ret!=0)
    {
        fprintf(stderr,"%s:%s\n",str,strerror(ret));
        pthread_exit(NULL);
    }
}
struct msg{
    int num;
    struct msg *next;
};
struct msg *head;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_data=PTHREAD_COND_INITIALIZER;

void *consumer(void *arg)
{
    while(1)
    {
        struct msg *mp;
        pthread_mutex_lock(&mutex);
        while(head==NULL)
        {
            pthread_cond_wait(&has_data,&mutex);    //原子操作，阻塞等待条件变量，解锁，并且被signal唤醒后wait会返回，重新加锁
        }
        mp=head;
        head=mp->next;
        pthread_mutex_unlock(&mutex);
        printf("---------consumer id %lu buy %d\n",pthread_self(),mp->num);
        free(mp);
        sleep(rand()%3);
    }



    return NULL;
}

void *producer(void *arg)
{
    while(1)
    {
        struct msg *mp;
        mp=malloc(sizeof(struct msg));
        mp->num=rand()%1000+1;
        printf("-----produce %d\n",mp->num);
        pthread_mutex_lock(&mutex);
        mp->next=head;
        head=mp;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&has_data);         //唤醒阻塞在条件变量has_data上的线程，可一次性唤醒多个
        sleep(rand()%3);
    }

    return NULL;
}
int main(int argc,char *argv)
{
    pthread_t cons,prod;
    int ret;
    srand(time(NULL));
    ret=pthread_create(&cons,NULL,consumer,NULL);
    if(ret!=0)
    {
        err_thread(ret,"consumer creat error");
    }

    ret=pthread_create(&cons,NULL,consumer,NULL);
    if(ret!=0)
    {
        err_thread(ret,"consumer creat error");
    }

    ret=pthread_create(&cons,NULL,consumer,NULL);
    if(ret!=0)
    {
        err_thread(ret,"consumer creat error");
    }

    pthread_create(&prod,NULL,producer,NULL);
    if(ret!=0)
    {
        err_thread(ret,"producer creat error");
    }
    pthread_join(cons,NULL);
    pthread_join(prod,NULL);
    return 0;


}