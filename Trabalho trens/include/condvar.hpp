#ifndef CONDVAR_HPP
#define CONDVAR_HPP

#include <pthread.h>

class condvar {
    struct node {
        pthread_mutex_t priv_mtx;
        node* prev;
    };

    node* front;
    node* back;
    pthread_mutex_t op_mtx;
public:
    condvar();
    ~condvar();
    void wait(pthread_mutex_t* mtx);
    void broadcast();
};

#endif