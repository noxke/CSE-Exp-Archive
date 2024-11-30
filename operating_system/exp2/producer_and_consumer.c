#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

// 产品缓冲区
int product_buf[10] = {0};
int product_num = 0;

// 缓冲区数量信号量
sem_t buf_num_sem;
// 缓冲区剩余空间信号量
sem_t buf_space_sem;

// 互斥锁 只能有一个生产者或者消费者能访问缓冲区
pthread_mutex_t buf_mutex;

static void *thread_producer(void *arg)
{
    int producer_id = *(int *)arg;
    printf("[producer %d] start\n", producer_id);
    for (int i = 0; i < 30; i++)
    {
        int sleep_time = ((rand() % 50) + 1) * 1000;
        int product = (rand() % 1000) + producer_id * 1000;
        usleep(sleep_time);
        // 需要缓冲区有空间
        sem_wait(&buf_space_sem);
        // 给缓冲区上锁
        pthread_mutex_lock(&buf_mutex);
        
        // 添加产品到缓冲区
        product_buf[product_num] = product;
        product_num++;
        printf("\n");
        printf("[producer %d] put %d to buf\n", producer_id, product);
        printf("[producer %d] product num in buf : %d\n", producer_id, product_num);

        // 释放缓冲区锁
        pthread_mutex_unlock(&buf_mutex);
        // 增加缓冲区产品数量
        sem_post(&buf_num_sem);
    }
    return NULL;
}

static void *thread_consumer(void *arg)
{
    int consumer_id = *(int *)arg;
    printf("[consumer %d] start\n", consumer_id);
    for (int i = 0; i < 20; i++)
    {
        int sleep_time = ((rand() % 100) + 1) * 1000;
        usleep(sleep_time);
        // 需要缓冲区有产品
        sem_wait(&buf_num_sem);
        // 给缓冲区上锁
        pthread_mutex_lock(&buf_mutex);

        // 从缓冲区取产品
        product_num--;
        int product = product_buf[product_num];
        product_buf[product_num] = 0;
        printf("\n");
        printf("[consumer %d] get %d from buf\n", consumer_id, product);
        printf("[consumer %d] product num in buf : %d\n", consumer_id, product_num);

        // 释放缓冲区锁
        pthread_mutex_unlock(&buf_mutex);
        // 释放缓冲区空间
        sem_post(&buf_space_sem);
    }
    return NULL;
}

int main()
{
    // 初始化随机数
    srand(time(NULL));
    // 初始化信号量
    sem_init(&buf_num_sem, 0, 0);
    sem_init(&buf_space_sem, 0, 10);
    // 初始化互斥锁
    pthread_mutex_init(&buf_mutex, NULL);
    // 创建2个生产者线程和3个消费者线程
    pthread_t thread_id[5];
    void *(*start_routine[5])(void *) = {thread_producer, thread_producer, thread_consumer, thread_consumer, thread_consumer};
    int arg[5] = {1, 2, 1, 2, 3};

    for (int i = 0; i < 5; i++)
    {
        int result = pthread_create(&thread_id[i], NULL, start_routine[i], (void*)&arg[i]);
        if (result != 0)
        {
            printf("[main] create thread %d failed\n", i);
        }
        printf("[main] create thread %d, thread_id : %ld\n", i, thread_id[i]);
    }
    // 等待所有线程结束
    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    // 销毁信号量
    sem_destroy(&buf_num_sem);
    sem_destroy(&buf_space_sem);
    // 销毁互斥锁
    pthread_mutex_destroy(&buf_mutex);
    return 0;
}