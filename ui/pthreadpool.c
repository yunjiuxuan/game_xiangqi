#include "pthreadpool.h"

// 线程工作函数
static void* thread_worker(void *arg)
{
    thread_pool_t *pool = (thread_pool_t *)arg;
    task_t *task = NULL;
    
    while (1)
    {
        pthread_mutex_lock(&pool->queue_mutex);
        
        // 等待任务或关闭信号
        while (pool->task_queue == NULL && !pool->shutdown)
        {
            pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
        }
        
        // 如果线程池关闭且队列为空，退出线程
        if (pool->shutdown && pool->task_queue == NULL)
        {
            pthread_mutex_unlock(&pool->queue_mutex);
            break;
        }
        
        // 从队列中取出任务
        task = pool->task_queue;
        if (task != NULL)
        {
            pool->task_queue = task->next;
            pool->queue_size--;
        }
        
        pthread_mutex_unlock(&pool->queue_mutex);
        
        // 执行任务
        if (task != NULL)
        {
            void *result = task->func(task->arg);
            free(task);
            (void)result;  // 忽略返回值
        }
    }
    
    return NULL;
}

// 初始化线程池
thread_pool_t* thread_pool_create(int pool_size)
{
    if (pool_size <= 0)
    {
        pool_size = DEFAULT_POOL_SIZE;
    }
    
    thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
    if (pool == NULL)
    {
        perror("创建线程池失败");
        return NULL;
    }
    
    memset(pool, 0, sizeof(thread_pool_t));
    pool->pool_size = pool_size;
    pool->task_queue = NULL;
    pool->queue_size = 0;
    pool->shutdown = 0;
    
    // 初始化互斥锁和条件变量
    pthread_mutex_init(&pool->queue_mutex, NULL);
    pthread_cond_init(&pool->queue_cond, NULL);
    
    // 创建线程
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * pool_size);
    if (pool->threads == NULL)
    {
        perror("创建线程数组失败");
        free(pool);
        return NULL;
    }
    
    // 创建工作线程
    for (int i = 0; i < pool_size; i++)
    {
        int ret = pthread_create(&pool->threads[i], NULL, thread_worker, pool);
        if (ret != 0)
        {
            perror("创建工作线程失败");
            // 清理已创建的线程
            pool->shutdown = 1;
            pthread_cond_broadcast(&pool->queue_cond);
            for (int j = 0; j < i; j++)
            {
                pthread_join(pool->threads[j], NULL);
            }
            free(pool->threads);
            free(pool);
            return NULL;
        }
    }
    
    printf("线程池创建成功，线程数量=%d\n", pool_size);
    return pool;
}

// 向线程池添加任务
int thread_pool_add_task(thread_pool_t *pool, void *(*func)(void *), void *arg)
{
    if (pool == NULL || func == NULL)
    {
        return -1;
    }
    
    // 创建任务
    task_t *task = (task_t *)malloc(sizeof(task_t));
    if (task == NULL)
    {
        perror("创建任务失败");
        return -1;
    }
    
    task->func = func;
    task->arg = arg;
    task->next = NULL;
    
    pthread_mutex_lock(&pool->queue_mutex);
    
    // 检查队列是否已满
    if (pool->queue_size >= MAX_TASKS)
    {
        pthread_mutex_unlock(&pool->queue_mutex);
        free(task);
        printf("警告：任务队列已满\n");
        return -1;
    }
    
    // 将任务添加到队列末尾
    if (pool->task_queue == NULL)
    {
        pool->task_queue = task;
    }
    else
    {
        task_t *p = pool->task_queue;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = task;
    }
    
    pool->queue_size++;
    
    // 通知工作线程有新任务
    pthread_cond_signal(&pool->queue_cond);
    
    pthread_mutex_unlock(&pool->queue_mutex);
    
    return 0;
}

// 关闭线程池
int thread_pool_destroy(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return -1;
    }
    
    pthread_mutex_lock(&pool->queue_mutex);
    
    // 设置关闭标志
    pool->shutdown = 1;
    
    // 唤醒所有工作线程
    pthread_cond_broadcast(&pool->queue_cond);
    
    pthread_mutex_unlock(&pool->queue_mutex);
    
    // 等待所有线程退出
    for (int i = 0; i < pool->pool_size; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }
    
    // 清理剩余任务
    task_t *task = pool->task_queue;
    while (task != NULL)
    {
        task_t *next = task->next;
        free(task);
        task = next;
    }
    
    // 释放资源
    free(pool->threads);
    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->queue_cond);
    free(pool);
    
    printf("线程池已关闭\n");
    return 0;
}

// 获取线程池状态
int thread_pool_get_queue_size(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return -1;
    }
    
    pthread_mutex_lock(&pool->queue_mutex);
    int size = pool->queue_size;
    pthread_mutex_unlock(&pool->queue_mutex);
    
    return size;
}
