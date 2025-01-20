// std
#include <iostream>
#include <string.h>
#include <chrono>
#include <unistd.h>

// my headers
#include <trains.hpp>

trains* trains::instance = nullptr;

void trains::train0() {
    while(true) {
        for (progress[0] = 0.0; progress[0] < 1; progress[0] += 0.1/velocities[0])
            usleep(0.1/velocities[0]);
        sem1.wait();
        pthread_mutex_lock(&L4);
    }
}

trains* trains::get_instance() {
    if (instance == nullptr)
        pthread_mutex_init(&L3, nullptr);
        pthread_mutex_init(&L4, nullptr);
        pthread_mutex_init(&L5, nullptr);
        pthread_mutex_init(&L6, nullptr);
        pthread_mutex_init(&L10, nullptr);
        for (int i = 0; i < 4; i++) {
            velocities[i] = 0.5;
            positions[i] = 0;
        }
        return new trains;
    return instance;
}