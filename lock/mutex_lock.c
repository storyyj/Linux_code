#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex;

void *tfn(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("hello ");
        sleep(1);
        printf("world!\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&tid,NULL,tfn,NULL);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(1);
        printf("WORLD!\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;


}