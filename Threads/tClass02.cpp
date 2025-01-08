
/*
 *  tClass02.cpp
 *
 *
 *  Created by Luiz Affonso on 04/05/22.
 *  Copyright 2022 __MyCompanyName__. All rights reserved.
 *
 */


// Utiliza a Class Thread existente na linguagem C++, a partir da versão 11.
// Programa (main) que cria threads, cujas funções têm parâmetros
// Para compilar utilizar: g++ --std=c++11 tClass02.cpp -o tclass02 -lpthread




// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <stdio.h>
 
void funcao(int x)
{
    std::cout << "Função"<< x << ": Vai dormir..\n";
    sleep(x);
   
    std::cout << "Função"<< x << ": Vou terminar..\n";
    
}



int main()
{
  
  std::thread thread1(funcao,10);   // Cria a thread1, que chama a função funcao(10)
  std::thread thread2 (funcao,15);  // Cria a thread2, que chama a função funcao(5)

  std::cout << "Função Main: As funções f1 e f2 estão executando concorrentemente.\n";

  // Sincronizar (juntar) as threads:
  thread1.join();     // Espera até a thread1 terminar
  thread2.join();      // Espera até a thread2 terminar

  std::cout << "Função Main: vai terminar.\n";

  return 0;
}
