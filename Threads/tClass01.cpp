
/*
 *  tClass01.cpp
 *
 *
 *  Created by Luiz Affonso on 04/05/22.
 *  Copyright 2022 __MyCompanyName__. All rights reserved.
 *
 */


// Utiliza a Class Thread existente na linguagem C++, a partir da versão 11.
// Programa (main) que cria duas threads e espera seus términos para também poder terminar.
// Utiliza variável global.
// Para compilar utilizar: g++ --std=c++11 tClass01.cpp -o tclass01 -lpthread




// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <stdio.h>
 
int x; 
 
void f1()
{
    std::cout << "Função f1: Vai dormir..\n";
    sleep(10);
    std::cout << "Função f1: Vai terminar..\n";
    
}

void f2()
{
    std::cout << "Função f2: processando..\n";
    sleep(x);
    std::cout << "Função f2: Vai terminar..\n";
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

  std::cout << "Função Main: f1 e f2 terminaram.\n";

  return 0;
}
