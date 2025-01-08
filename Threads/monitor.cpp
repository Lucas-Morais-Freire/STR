#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (){
	printf("Início do programa Monitor\n");
	
    while(1) {
		 printf("\n\n\n\n");
          //system("pstree auf| grep thread");
          //system("ps uj -U $USER | grep thread ");
          system("ps u| grep thread");
          sleep(1);
          system("clear");
    }
	exit (0);
}


