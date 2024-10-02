/*
 *  gmtime.cpp
 *  
 *
 *  Created by Luiz Affonso Guedes on 22/03/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// UFRN-CT-DCA
// Manipulação de tempo em c,c++
// Programa: programa que manipula a struct tm

#include <iostream> //cout
#include <time.h>   //para: gmtime()
using namespace std;

int  main ( ){
	// um ponteiro para a estrutura tm
	struct tm *tm_ptr;  
	// variável para armazenar o tempo em segundos
	time_t  tempo_valor;
	time_t  tempo_valor2;
	
	// armazenar o tempo
	time(&tempo_valor);
	// obtendo a esttutura
	
    
        //tm_ptr = gmtime(&tempo_valor);
    
        tm_ptr = localtime(&tempo_valor);

	
	cout << "Instante atual: " << tm_ptr->tm_mday << "/" << tm_ptr->tm_mon+1 << "/" << tm_ptr->tm_year+1900 << "\t" << tm_ptr->tm_hour << ":" << tm_ptr->tm_min << ":" << tm_ptr->tm_sec << "\n";
	
	tempo_valor2 = mktime(tm_ptr);
	
	cout << "tempo_valor = " << tempo_valor <<"\n";
	cout << "tempo_valor2 = " << tempo_valor2 <<"\n";
}

