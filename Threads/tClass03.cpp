
/*
 *  tClass03.cpp
 *
 *
 *  Created by Luiz Affonso on 04/05/22.
 *  Copyright 2022 __MyCompanyName__. All rights reserved.
 *
 */


// Utiliza a Class Thread existente na linguagem C++, a partir da versão 11.
// Programa (main) que cria threads de diversas formas
// Para compilar utilizar: g++ --std=c++11 tClass03.cpp -o tclass03 -lpthread

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
 
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 (função f1(.))executando ...\n";
        ++n;
        // a thread vai dormir por 10 milisegundos
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 (função f2(.)) executando ...\n";
        ++n;
        // a thread vai dormir por 10 milisegundos
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
class classe1
{
public:
    void metodo1()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 3 (metodo1 da classe1) executando ... \n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};
 
class classe2
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 4 (operator da classe2) executando ...\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};
 
int main()
{
    int n = 0;
    classe1 obj1;
    classe2 obj2;
    
    std::thread t1; // t1 não é uma thread
    std::thread t2(f1, n + 1); // passagem por valor
    std::thread t3(f2, std::ref(n)); // passagem de valor por refência
    std::thread t4(std::move(t3)); // t4 está executando f2(). t3 não está mais executando
    std::thread t5(&classe1::metodo1, &obj1); // t5 executa classe1::metodo1() no objeto obj1
    std::thread t6(obj2); // t6 executa classe2::operator() no objeto obj2
    t2.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "Main: o valor final de n é " << n << '\n';
    std::cout << "Main: o valor final de obj1.n (obj1::n) é " << obj1.n << '\n';
    std::cout << "Main: o valor fianl de obj2.n (obj2::n) é " << obj2.n << '\n';
}
