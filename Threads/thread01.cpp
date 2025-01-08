
/*
 *  thread01.cpp
 *  teste
 *
 *  Created by Luiz Affonso on 04/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

// programa thread01.cpp
// Programa que cria uma thread e espera seu término para também poder terminar 
// Para compilá-lo utilise: g++ -o thread01 thread01.cpp -lpthread



//#include "thread01.h"


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>   // biblioteca pthread


void *thread_function(void *arg);

char message[] = "Alô, Mundo cruel!";

int main() {
    int res;
    pthread_t a_thread;  // declaração de uma thread
    void *thread_result; //NULL
	
    // criação de thread: (endereco_da_thread, atributos_da_thread, endereco_da_função, argumentos_da_função)
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    
    //  Controle de erro na criação da thread   //
    if (res != 0) {
        perror("A Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    
    
    printf("MAIN()--> Esperando pelo término da thread...\n");
  

   // Esperar a thread terminar
   
    //res = pthread_join(a_thread, &thread_result);
    //if (res != 0) {
     //   perror("O thread_join falhou");
     //  exit(EXIT_FAILURE);
    //}
    sleep(1);
    
    printf("MAIN()--> O thread_join retornou:   %s\n", (char *)thread_result);
    printf("MAIN()--> Message agora é: %s\n\n", message);
    printf("MAIN()--> Vai esperar 3 segundos para terminar \n");
    sleep(3);
    exit(EXIT_SUCCESS);   // fim da thread main()
}

void *thread_function(void *arg) {
    printf("THREAD--> thread_function está rodando. O argumento foi %s\n", (char *)arg);
    printf("THREAD--> Agora vou dormir por 5 segundos\n");
    sleep(5);
    printf("THREAD--> Acordei e agora vou terminar\n");
    strcpy(message, "Estou indo embora! (escrito pela thread)");
    pthread_exit((void *) "Obrigado pelo seu tempo de CPU");    // fim da thread a_thread
}
