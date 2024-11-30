#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

static void *thread1_proc(void *arg)
{
    for (int i = 1; i <= 1000; i++)
    {
        printf("A: %4d\t", i);
        usleep(10000);
    }
    return NULL;
}

static void *thread2_proc(void *arg)
{
    for (int i = 1000; i > 0; i--)
    {
        printf("B: %4d\t", i);
        usleep(10000);
    }
    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    // 创建A线程
    pthread_create(&thread1, NULL, thread1_proc, NULL);
    // 创建B线程
    pthread_create(&thread2, NULL, thread2_proc, NULL);
    // 等待进程A结束
    //pthread_join(thread1, NULL);
    // 等待进程B结束
    //pthread_join(thread2, NULL);
    return 0;
}
