//
//  thread07.cpp
//  
//
//  Created by Affonso
//
//



// Programa que sincroniza threads utilizando-se mutexes
// Para compilá-lo utilise: g++ -o thread07 thread07.cpp -lpthread


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);
void *thread_function3(void *arg);

pthread_mutex_t work_mutex1, work_mutex2; /* declaração de um mutex */

#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;

int main() {
    int res;
    pthread_t thread1, thread2, thread3;  // declaração de 03 threads
    void *thread_result;
    
    res = pthread_mutex_init(&work_mutex1, NULL);   // criação do mutex
    if (res != 0) {
        perror("Iniciação do Mutex 1 falhou");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_mutex_init(&work_mutex2, NULL);   // criação do mutex
    if (res != 0) {
        perror("Iniciação do Mutex 2 falhou");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&thread1, NULL, thread_function1, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    printf("Criação da Thread1 \n");
    
    res = pthread_create(&thread2, NULL, thread_function2, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
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
        perror("Junção da Thread3 falhou");
        exit(EXIT_FAILURE);
    }
    printf("MAIN() --> Thread3 foi juntada com sucesso\n");
    
    pthread_mutex_destroy(&work_mutex1);  // destruição do mutex1
    pthread_mutex_destroy(&work_mutex2);
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg) {
    while(1)
        {
            printf("Trem1 - Trilho L1 \n");
            sleep(1);
            
            printf("Trem1 - Trilho L2 \n");
            sleep(1);
            
            pthread_mutex_lock(&work_mutex1);
            printf("\tTrem1 - Trilho L3 \n");
            sleep(1);
            pthread_mutex_unlock(&work_mutex1);
            
            printf("Trem1 - Trilho L4 \n");
            sleep(1);
        }
    pthread_exit(0);
}


void *thread_function2(void *arg) {
        int v = 3;
        while(1)
            {
            pthread_mutex_lock(&work_mutex2);
            printf("\tTrem2 - Trilho L5 \n");
            sleep(v);
            pthread_mutex_unlock(&work_mutex2);
            
            printf("Trem2 - Trilho L6 \n");
            sleep(v);
            
            pthread_mutex_lock(&work_mutex1);
            printf("\t\tTrem2 - Trilho L3 \n");
            sleep(10*v);
            pthread_mutex_unlock(&work_mutex1);
            
            printf("Trem2 - Trilho L7 \n");
            sleep(v);
            }
            pthread_exit(0);
}
    
 void *thread_function3(void *arg) {
 	int v = 2;
        while(1)
            {
            printf("Trem3 - Trilho L9 \n");
            sleep(v);
            
            pthread_mutex_lock(&work_mutex2);
            printf("\t\tTrem3 - Trilho L5 \n");
            sleep(v);
            pthread_mutex_unlock(&work_mutex2);
          
            printf("Trem3 - Trilho L10 \n");
            sleep(v);
            
            
            printf("Trem3 - Trilho L8 \n");
            sleep(v);
            }
            pthread_exit(0);
}
