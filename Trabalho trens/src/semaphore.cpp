#include <stdio.h>

#include <semaphore.hpp>

semaphore::semaphore(int resrc_cnt) : resrc_cnt(resrc_cnt)
{
    pthread_mutex_init(&op_lock, nullptr);
}

semaphore::~semaphore()
{
    pthread_mutex_destroy(&op_lock);
}

void semaphore::post()
{
    pthread_mutex_lock(&op_lock);
    resrc_cnt++;
    cv.broadcast();
    pthread_mutex_unlock(&op_lock);
}

void semaphore::wait()
{
    pthread_mutex_lock(&op_lock);
    while(resrc_cnt == 0) {
        cv.wait(&op_lock);
    }
    resrc_cnt--;
    pthread_mutex_unlock(&op_lock);
}