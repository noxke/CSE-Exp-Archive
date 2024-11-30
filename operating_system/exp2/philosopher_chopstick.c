#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define NUM 5
// 筷子 每根筷子只能由一个线程访问
pthread_mutex_t chopstick[NUM];

// 哲学家线程函数
static void *philospher(void *arg)
{
    int id = *(int *)arg;
    int l_chopstick = id;
    int r_chopstick = (id + 1) % NUM;
    printf("[philospher %d] thread start\n", id);
    for (int i = 0; i < 50; i++)
    {
        // 思考
        int think_time = ((rand() % 400) + 101) * 1000;
        printf("[philospher %d] thinking\n", id);
        usleep(think_time);
        // 休息
        int sleep_time = ((rand() % 400) + 101) * 1000;
        printf("[philospher %d] sleeping\n", id);
        usleep(sleep_time);

        // 拿起左侧筷子
        pthread_mutex_lock(&chopstick[l_chopstick]);
        printf("[philospher %d] pick up left chopstick %d\n", id, l_chopstick);
        // 拿起右侧筷子
        pthread_mutex_lock(&chopstick[r_chopstick]);
        printf("[philospher %d] pick up right chopstick %d\n", id, r_chopstick);
        // 吃饭
        int eat_time = ((rand() % 400) + 101) * 1000;
        usleep(eat_time);
        printf("[philospher %d] eatting\n", id);
        // 放下左侧筷子
        pthread_mutex_unlock(&chopstick[l_chopstick]);
        printf("[philospher %d] put down left chopstick %d\n", id, l_chopstick);
        // 放下右侧筷子
        pthread_mutex_unlock(&chopstick[r_chopstick]);
        printf("[philospher %d] put down right chopstick %d\n", id, r_chopstick);
    }
    return NULL;
}

int main()
{
    // 初始化随机数
    srand(time(NULL));
    // 初始化互斥锁
    for (int i = 0; i < NUM; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }
    pthread_t thread_id[NUM];
    int arg[NUM];
    // 创建5个哲学家线程
    for (int i = 0; i < NUM; i++)
    {
        arg[i] = i;
        int result = pthread_create(&thread_id[i], NULL, philospher, (void*)&arg[i]);
        if (result != 0)
        {
            printf("[main] create thread %d failed\n", i);
        }
        printf("[main] create thread %d, thread_id : %ld\n", i, thread_id[i]);
    }
    // 等待所有线程结束
    for (int i = 0; i < NUM; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    // 销毁互斥锁
    for (int i = 0; i < NUM; i++)
    {
        pthread_mutex_destroy(&chopstick[i]);
    }
    return 0;
}