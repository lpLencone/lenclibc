#include "thread-pool.h"

#include <stdlib.h>

void *thread_job(void *arg);

struct thread_pool thread_pool_init(int n_threads)
{
    struct thread_pool thread_pool;
    thread_pool.n_threads = n_threads;
    thread_pool.active = 1;
    thread_pool.pool = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&thread_pool.pool[i], NULL, thread_job,  NULL);
    }
    thread_pool.work = queue_init();
    thread_pool.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    thread_pool.signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    return thread_pool;
}

void *thread_job(void *arg)
{
    
}