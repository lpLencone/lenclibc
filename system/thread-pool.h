#ifndef thread_pool_h
#define thread_pool_h

#include "../data-structures/queue/queue.h"

#include <pthread.h>

struct thread_pool
{
    int n_threads;
    int active;
    struct queue work;
    pthread_t *pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;
};

struct thread_job
{
    void *(*job)(void *arg);
    void *arg;
};

struct thread_pool thread_pool_init(int n_threads);
struct thread_job  thread_job_init(void *(*job)(void *arg), void *arg);

#endif /* thread_pool_h */

