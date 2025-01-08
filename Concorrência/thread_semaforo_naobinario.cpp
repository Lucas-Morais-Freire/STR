//
//  thread_semaforo_naobinario2.cpp
//  Só funciona em Linux, não em MAC
//
//  Created by Affonso on 24/10/17.
//
// http:pubs.opengroup.org/onlinepubs/7908799/xsh/sem_post.html

// programa thread10.cpp
// Programa que sincroniza threads utilizando-se semáforo não binário
// Para compilá-lo utilise: g++ -o thread_semaforo_naobinario thread_semforo_naobinario.cpp -lpthread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);
void *thread_function3(void *arg);
sem_t not_bin_sem;

int main() {
    int res;
    pthread_t thread1, thread2, thread3;  // declaração de 03 threads
    void *thread_result;
    
    res = sem_init(&not_bin_sem, 0, 2);
    if (res < 0) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&thread1, NULL, thread_function1, NULL);
    if (res != 0) {
        perror("Criação da Thread2 falhou");
        exit(EXIT_FAILURE);
    }
    printf("Criação da Thread1 \n");
    
    res = pthread_create(&thread2, NULL, thread_function2, NULL);
    if (res != 0) {
        perror("Criação da Thread2 falhou");
        exit(EXIT_FAILURE);
    }
    printf("Criação da Thread2 \n");
    
    res = pthread_create(&thread3, NULL, thread_function3, NULL);
    if (res != 0) {
        perror("Criação da Thread3 falhou");
        exit(EXIT_FAILURE);
    }
    printf("Criação da Thread3 \n");
    
    res = pthread_join(thread1, &thread_result);
    if (res != 0) {
        perror("Junção da Thread1 falhou");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> Thread1 foi juntada com sucesso\n");
    
    res = pthread_join(thread2, &thread_result);
    if (res != 0) {
        perror("Junção da Thread2 falhou");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> Thread2 foi juntada com sucesso\n");
    
    res = pthread_join(thread3, &thread_result);
    if (res != 0) {
        perror("Junção da Thread2\3 falhou");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> Thread3 foi juntada com sucesso\n");
    
    printf("MAIN() --> A THREAD main vai terminar\n");
    
    sem_destroy(&not_bin_sem);
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg) {
    sleep(1);
    while(1)
    {
        printf("Thread1 -- Fora da região crítica \n");
        sleep(1);
        sem_wait(&not_bin_sem);
        printf("Thread1 -- Dentro da região crítica \n");
        sleep(1);
        sem_post(&not_bin_sem);
        
    }
    pthread_exit(0);
}


void *thread_function2(void *arg) {
    sleep(1);
    while(1)
    {
        printf("Thread2 -- Fora da região crítica \n");
        sleep(1);
        sem_wait(&not_bin_sem);
        printf("Thread2 -- Dentro da região crítica \n");
        sleep(1);
        sem_post(&not_bin_sem);
    }
    pthread_exit(0);
}

void *thread_function3(void *arg) {
    sleep(1);
    while(1)
    {
        printf("Thread3 -- Fora da região crítica \n");
        sleep(1);
        sem_wait(&not_bin_sem);
        printf("Thread3 -- Dentro da região crítica \n");
        sleep(10);
        sem_post(&not_bin_sem);
    }
    pthread_exit(0);
}
