/*
 *  ordenacao.cpp
 *  
 *
 *  Created by Luiz Affonso Guedes on 06/03/17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

// UFRN-CT-DCA
// Programa: programa para ordenação de um vetor

// Manipulação de tempo em c,c++
// Programa: programa que usa manipuladores de tempo para 
// medir o desempenho de algoritmos de ordenação


#include <cstdlib>   //qsort
#include  <time.h>   // clock(),time()
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <sys/time.h>
#include <fstream>
#include <iostream>

//Vetores usados pelos métodos de ordenação

//Função usada pelo qsort para comparar dois numeros
int compare_ints( const void* a, const void* b ) {
	int* arg1 = (int*) a;
	int* arg2 = (int*) b;
	if( *arg1 < *arg2 ) return -1;
	else if( *arg1 == *arg2 ) return 0;
	else return 1;
}

//Algoritmos de ordenação bubble sort
void bubbleSort(int *vetor, int tamanho) {
	int aux;
	for (int i = 0; i < tamanho-1; i++) {
		for (int j = 0; j < tamanho-1; j++) {
			if (vetor[j] > vetor[j+1]) {
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
}


//Observe que os números são gerados aleatoriamente baseados
//em uma semente. Se for passado a mesma semente, os 
//números aleatórios serão os mesmos
void criarVetor(int** vqsort, int** vbsort, int tamanhoVetor, int semente){
	srand (semente);
	(*vqsort) = new int[tamanhoVetor];
	(*vbsort) = new int[tamanhoVetor];
	for (int i=0;i<tamanhoVetor;i++){
		(*vqsort)[i] =  rand()%100000;
        (*vbsort)[i] = (*vqsort)[i]; // utilizar os mesmos valores
		//vetorBubbleSort[i] = rand()%100000;
	}
}

#define N_RUNS 5
#define N 10

int main ()
{
	//Tamanho do vetor
	timeval ti, tf;
	int* vqsort,* vbsort;
	int n;

	long qsort_times[N][N_RUNS];
	long bsort_times[N][N_RUNS];

	for (int j = 0; j < N_RUNS; j++) {
		n = 125;
		for (int i = 0; i < N; i++) {
			std::cout << "com n = " << n << '\n';
			criarVetor(&vqsort, &vbsort, n, 23);
			//Ordenar utilizando quickSort
			gettimeofday(&ti, nullptr);
			qsort (vqsort, n, sizeof(int), compare_ints);
			gettimeofday(&tf, nullptr);
			qsort_times[i][j] = 1000000*(tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec);

			//Ordenar utilizando bubleSort
			gettimeofday(&ti, nullptr);
			bubbleSort(vbsort,n);
			gettimeofday(&tf, nullptr);
			bsort_times[i][j] = 1000000*(tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec);

			delete[] vbsort;
			delete[] vqsort;

			n <<= 1;
		}
	}
	std::ofstream file("times.csv");

	n = 125;
	file << "quicksort\n";
	file << "size,time(us)\n";
	for (int i = 0; i < N; i++) {
		double total = 0.0;
		for (int j = 0; j < N_RUNS; j++) {
			total += qsort_times[i][j];
		}
		file << n << ',' << total / N_RUNS << '\n';
		n <<= 1;
	}

	n = 125;
	file << "\nbubblesort\n";
	file << "size,time(us)\n";
	for (int i = 0; i < N; i++) {
		double total = 0.0;
		for (int j = 0; j < N_RUNS; j++) {
			total += bsort_times[i][j];
		}
		file << n << ',' << total / N_RUNS << '\n';
		n <<= 1;
	}

	file.close();

    printf("terminou");

	system("python ./plot_sorts.py");
	exit(0);
}


