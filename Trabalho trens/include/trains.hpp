#ifndef TRAINS_HPP
#define TRAINS_HPP

#include <semaphore.hpp>

class trains {
    static trains* instance;

    void train0();
    void train1();
    void train2();
    void train3();

    static pthread_mutex_t L3, L4, L5, L6, L10;
    semaphore sem1, sem2;

    static double progress[4];
    static double velocities[4];

    trains() : sem1(2), sem2(2) {}
public:
    trains(const trains&) = delete;
    trains& operator=(const trains&) = delete;
    static trains* get_instance();
};

#endif