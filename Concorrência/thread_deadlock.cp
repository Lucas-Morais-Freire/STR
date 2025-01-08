//
//  thread_deadlock.cpp
//  
//
//  Created by Affonso
//
//



// Programa que sincroniza threads utilizando 02 mutexes com deadlock
// Para compilá-lo utilise: g++ -o thread_deadlock thread_deadlock.cpp -lpthread


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);

pthread_mutex_t mutex1, mutex2; /* declaração de um mutex */



int main() {
    int res;
    pthread_t thread1, thread2;  // declaração de 02 trheads
    void *thread_result;
    
    res = pthread_mutex_init(&mutex1, NULL);   // criação do mutex1
    if (res != 0) {
        perror("Iniciação do Mutex1 falhou");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_mutex_init(&mutex2, NULL);   // criação do mutex2
    if (res != 0) {
        perror("Iniciação do Mutex2 falhou");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&thread1, NULL, thread_function1, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    printf("Main() -- Criação da Thread1 \n");
    
    res = pthread_create(&thread2, NULL, thread_function2, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    printf("Main() -- Criação da Thread2 \n");
    
    res = pthread_join(thread1, &thread_result);
    if (res != 0) {
        perror("Junção da Thread1 falhou");
        exit(EXIT_FAILURE);
    }
    printf("Main() -- Thread1 foi juntada com sucesso\n");
    
    res = pthread_join(thread2, &thread_result);
    if (res != 0) {
        perror("Junção da Thread2 falhou");
        exit(EXIT_FAILURE);
    }
    printf("Main() -- Thread2 foi juntada com sucesso\n");
    
    
    pthread_mutex_destroy(&mutex1);  // destruição do mutex1
    pthread_mutex_destroy(&mutex2);  // destruição do mutex2
    
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg) {
    sleep(1);
    while(1)
    {
        printf("Thread1 -- Fora das Regiões Críticas A e B \n");
        sleep(1);
        printf("Thread1 -- Vai entrar na Região Crítica A\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread1 -- Dentro da Região Crítica A \n");
        sleep(1);
        printf("Thread1 -- Vai entrar na Região Crítica B \n");
        pthread_mutex_lock(&mutex2);
        printf("Thread1 -- Dentro das Regiões Críticas A e B \n");
        sleep(1);
        pthread_mutex_unlock(&mutex1);
        printf("Thread1 -- Dentro da Região Crítica B e Fora da Região Crítica A\n");
        pthread_mutex_unlock(&mutex2);
    }
    pthread_exit(0);
}


void *thread_function2(void *arg) {
    sleep(2);
    while(1)
    {
        printf("Thread2 -- Fora das Regiões Críticas A e B \n");
        sleep(1);
        printf("Thread2 -- Vai entrar na Região Crítica B\n");
        pthread_mutex_lock(&mutex2);
        printf("Thread2 -- Dentro da Região Crítica B\n");
        sleep(1);
        printf("Thread2 -- Vai entrar na Região Crítica A\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread2 -- Dentro das Regiões Críticas A e B \n");
        sleep(1);
        pthread_mutex_unlock(&mutex2);
        printf("Thread2 -- Dentro da Região Crítica A e Fora da Região Crítica B\n");
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(0);
}

