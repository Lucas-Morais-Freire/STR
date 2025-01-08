
/*
 *  tClass04.cpp
 *
 *
 *  Created by Luiz Affonso on 04/05/22.
 *  Copyright 2022 __MyCompanyName__. All rights reserved.
 *
 */


// Utiliza a Class Thread existente na linguagem C++, a partir da versão 11.
// Além disto se investiga o se muda a prioridade de uma thread
// Programa (main) que cria threads, cujas funções têm parâmetros


// Para compilar utilizar: g++ --std=c++11 tClass04.cpp -o tclass04 -lpthread




// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <stdio.h>
 
void funcao(int x)
{
    std::cout << "Começo da Função "<< x << "\n";
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "Função "<< x << " tem ID \n" << std::this_thread::get_id();
    
    std::cout << "Função "<< x << " vai dormir por "<< x << " segundos.\n";
    sleep(x);
    std::cout << "Função " << x <<" acordou e vai mudar a sua prioridade.\n";
    nice(x);  // mudança de prioridade da thread.
    std::cout << "Função " << x << " vai dormir por mais "<< x << " segundos.\n";
    sleep(x);
    std::cout << "Função"<< x << " vai terminar..\n";
    
}



int main()
{
  
  std::thread thread1(funcao,5);   // Cria a thread1, que chama a função funcao
  std::thread thread2 (funcao,7);  // Cria a thread2, que chama a função funcao

  std::cout << "Função Main: As funções f15 e f7 estão executando concorrentemente.\n";

  std::cout << "Função Main: O ID da thread Main é " << std::this_thread::get_id() <<"\n";
  std::cout << "Função Main: O ID da thread thread1 é " << thread1.get_id() <<"\n";
  std::cout << "Função Main: O ID da thread thread2 é " << thread2.get_id() <<"\n";
    
  // Sincronizar (juntar) as threads:
    
  thread1.join();     // Espera até a thread1 terminar
  thread2.join();      // Espera até a thread2 terminar

  std::cout << "Função Main: vai terminar.\n";

  return 0;
}
