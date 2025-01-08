
/*
 *  tClass01.cpp
 *
 *
 *  Created by Luiz Affonso on 04/05/22.
 *  Copyright 2022 __MyCompanyName__. All rights reserved.
 *
 */


// Utiliza a Class Thread existente na linguagem C++, a partir da versão 11.
// Programa (main) que cria duas threads e um multex.
// Utiliza variável global.
// Para compilar utilizar: g++ --std=c++11 tClass07.cpp -o tClass07 -lpthread




// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // mutex
#include <unistd.h>
#include <stdio.h>
 
int x; 
std::mutex mtx1;

void f1()
{
     while(1) {
        std::cout << "Função f1: Fora da região crítica.\n";
        sleep(2);
        mtx1.lock();  // Bloqueando o acesso à seção crítica com um mutex
        std::cout << "Função f1: entrou na região crítica.\n";
        sleep(10);
        std::cout << "Função f1: Vai sair da região crítica.\n";
        mtx1.unlock();    // Desbloqueando o mutex após a conclusão da manipulação
    }
    
}

void f2()
{
    while(1) {
        std::cout << "Função f2: Fora da região crítica.\n";
        sleep(2);
        mtx1.lock();  // Bloqueando o acesso à seção crítica com um mutex
        std::cout << "Função f2: entrou na região crítica.\n";
        sleep(2);
        std::cout << "Função f2: Vai sair da região crítica.\n";
        mtx1.unlock();    // Desbloqueando o mutex após a conclusão da manipulação
    }
}



int main()
{
  x = 15;
  
  std::thread thread1 (f1);   // Cria a thread1, que chama a função f1()
  std::thread thread2 (f2);  // Cria a thread2, que chama a função f2()

  std::cout << "Função Main: As funções f1 e f2 estão executando concorrentemente.\n";
 
  // Sincronizar (juntar) as threads:
  thread1.join();     // Espera até a thread1 terminar
  thread2.join();      // Espera até a thread2 terminar
  
  std::cout << "Função Main: vai executar o sleep().\n";
  sleep(10);

  std::cout << "Função Main: f1 e f2 terminaram.\n";

  return 0;
}
