#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 默认线程池大小
#define DEFAULT_POOL_SIZE 4
#define MAX_TASKS 1024

// 任务结构体
typedef struct task {
    void *(*func)(void *);  // 任务函数指针
    void *arg;              // 任务参数
    struct task *next;      // 下一个任务
} task_t;

// 线程池结构体
typedef struct thread_pool {
    pthread_t *threads;     // 线程数组
    int pool_size;          // 线程池大小
    task_t *task_queue;     // 任务队列
    int queue_size;         // 队列中任务数量
    int shutdown;           // 关闭标志
    
    pthread_mutex_t queue_mutex;  // 任务队列互斥锁
    pthread_cond_t queue_cond;    // 任务队列条件变量
} thread_pool_t;

// 初始化线程池
thread_pool_t* thread_pool_create(int pool_size);

// 向线程池添加任务
int thread_pool_add_task(thread_pool_t *pool, void *(*func)(void *), void *arg);

// 关闭线程池
int thread_pool_destroy(thread_pool_t *pool);

// 获取线程池状态
int thread_pool_get_queue_size(thread_pool_t *pool);

#endif // __PTHREAD_POOL_H__
