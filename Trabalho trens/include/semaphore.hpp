#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <pthread.h>
#include <condvar.hpp>

class semaphore {
    pthread_mutex_t op_lock;
    int resrc_cnt;
    condvar cv;
public:
    semaphore(int resrc_cnt);
    ~semaphore();
    void post();
    void wait();
};

#endif