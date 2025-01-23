// std
#include <iostream>
#include <string.h>
#include <chrono>

// my headers
#include <trains.hpp>

pthread_mutex_t trains::inst_mtx = PTHREAD_MUTEX_INITIALIZER;
trains* trains::instance = nullptr;
pthread_mutex_t trains::L3;
pthread_mutex_t trains::L4;
pthread_mutex_t trains::L5;
pthread_mutex_t trains::L6;
pthread_mutex_t trains::L10;
pthread_mutex_t trains::prog_mtxs[4];
double trains::progress[4];

pthread_mutex_t trains::vel_mtxs[4];
double trains::velocities[4];

useconds_t trains::period;

void trains::train0() {
    while(true) {
        // esperar chegar em 1 metro
        train_wait(0, 0.0, 1.0);
        
        sem3.wait();
        sem1.wait();             // tentar entrar na interseccao 1
        pthread_mutex_lock(&L4); // tentar entrar no trilho 4

        train_wait(0, 1.0, 2.0); // esperar chegar em 2 metros

        sem2.wait();               // tentar entrar na interseccao 2
        pthread_mutex_lock(&L6);   // tentar entrar no trilho 6
        pthread_mutex_unlock(&L4); // sair do trilho 4
        sem1.post();               // sair da interseccao 1
        sem3.post();

        train_wait(0, 2.0, 3.0); // esperar chegar em 3 metros

        pthread_mutex_lock(&L10);  // tentar entrar no trilho 10
        pthread_mutex_unlock(&L6); // sair do trilho 6
        sem2.post();               // sair da interseccao 2

        train_wait(0, 3.0, 4.0); // esperar chegar em 4 metros

        pthread_mutex_unlock(&L10); // sair do trilho 10

        train_wait(0, 4.0, 8.0);    // esperar chegar em 8 metros (final)
    }
}

void trains::train1() {
    while(true) {
        // esperar chegar em 1 metro
        train_wait(1, 0.0, 1.0);
        
        sem3.wait();
        sem1.wait();             // entrar na interseccao 1
        pthread_mutex_lock(&L3); // tentar entrar no trilho 3

        train_wait(1, 1.0, 2.0);

        pthread_mutex_lock(&L4);   // tentar pegar o trilho 4
        pthread_mutex_unlock(&L3); // sair do trilho 3
        sem1.post();               // sair da interseccao 1
        sem3.post();

        train_wait(1, 2.0, 3.0);

        pthread_mutex_unlock(&L4); // sair do trilho 4

        train_wait(1, 3.0, 4.0); 
    }
}
void trains::train2() {
    while(true) {
        train_wait(2, 0.0, 1.0);

        sem3.wait();
        sem2.wait();             // entrar na interseccao 2
        pthread_mutex_lock(&L5); // tentar entrar no trilho 5

        train_wait(2, 1.0, 2.0);

        sem1.wait();               // tentar entrar na interseccao 1 
        pthread_mutex_lock(&L6);   // tentar entrar no trilho 6
        pthread_mutex_unlock(&L5); // sair do trilho 5
        sem2.post();               // sair da interseccao 2
        sem3.post();

        train_wait(2, 2.0, 3.0);

        pthread_mutex_lock(&L3);   // tentar entrar no trilho 3
        pthread_mutex_unlock(&L6); // sair do trilho 6
        sem1.post();               // sair da interseccao 1

        train_wait(2, 3.0, 4.0);

        pthread_mutex_unlock(&L3); // sair do trilho 3
    }
}

void trains::train3() {
    while(true) {
        train_wait(3, 0.0, 2.0);

        sem3.wait();
        sem2.wait();              // tentar entrar na interseccao 2
        pthread_mutex_lock(&L10); // tentar entrar no trilho 10

        train_wait(3, 2.0, 3.0);

        pthread_mutex_lock(&L5);    // tentar entrar no trilho 5
        pthread_mutex_unlock(&L10); // sair do trilho 10
        sem2.post();                // sair da interseccao 2
        sem3.post();

        train_wait(3, 3.0, 4.0);

        pthread_mutex_unlock(&L5); // sair do trilho 5
    }
}

void trains::train_wait(int train_idx, double start, double end)
{
    // modify progress variable (start)  
    pthread_mutex_lock(&prog_mtxs[train_idx]);
    progress[train_idx] = start;
    pthread_mutex_unlock(&prog_mtxs[train_idx]);

    while (progress[train_idx] < end) {
        usleep(period); // sleep for this period of time

        // acquire velocity
        pthread_mutex_lock(&vel_mtxs[train_idx]);
        double vel = velocities[train_idx]/1000000; // convert to us.
        pthread_mutex_unlock(&vel_mtxs[train_idx]);

        // update progress
        pthread_mutex_lock(&prog_mtxs[train_idx]);
        progress[train_idx] = progress[train_idx] + period*vel > end ? end : progress[train_idx] + period*vel;
        pthread_mutex_unlock(&prog_mtxs[train_idx]);
    }
}

trains* trains::get_instance(useconds_t period) {
    pthread_mutex_lock(&inst_mtx);
    if (instance == nullptr) {
        trains::period = period;

        pthread_mutex_init(&L3, nullptr);
        pthread_mutex_init(&L4, nullptr);
        pthread_mutex_init(&L5, nullptr);
        pthread_mutex_init(&L6, nullptr);
        pthread_mutex_init(&L10, nullptr);
        for (int i = 0; i < 4; i++) {
            pthread_mutex_init(&prog_mtxs[i], nullptr);
            pthread_mutex_init(&vel_mtxs[i], nullptr);
            velocities[i] = 0.5;
            progress[i] = 0.0;
        }
        instance = new trains;
        pthread_mutex_unlock(&inst_mtx);
        return instance;
    }
    pthread_mutex_unlock(&inst_mtx);
    return instance;
}

double trains::get_progress(int i) {
    pthread_mutex_lock(&prog_mtxs[i]);
    double ret = progress[i];
    pthread_mutex_unlock(&prog_mtxs[i]);
    return ret;
}

void trains::set_velocity(int i, double vel) {
    pthread_mutex_lock(&vel_mtxs[i]);
    velocities[i] = vel;
    pthread_mutex_unlock(&vel_mtxs[i]);
}