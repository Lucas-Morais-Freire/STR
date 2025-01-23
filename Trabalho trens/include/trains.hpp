#ifndef TRAINS_HPP
#define TRAINS_HPP

// std
#include <unistd.h>

// my headers
#include <semaphore.hpp>

class trains {
    static pthread_mutex_t inst_mtx;
    static trains* instance;

    void train_wait(int train_idx, double start, double end);

    static pthread_mutex_t L3, L4, L5, L6, L10;
    semaphore sem1, sem2, sem3;

    static pthread_mutex_t prog_mtxs[4];
    static double progress[4];

    static pthread_mutex_t vel_mtxs[4];
    static double velocities[4];

    static useconds_t period;

    trains() : sem1(2), sem2(2), sem3(3) {}
public:
    trains(const trains&) = delete;
    trains& operator=(const trains&) = delete;
    static trains* get_instance(useconds_t period = 17000);
    double get_progress(int i);
    void set_velocity(int i, double vel);
    void train0();
    void train1();
    void train2();
    void train3();
};

#endif