//
//  cliente6.cpp
//  
//
//  Created by Affonso on 25/04/16.
//
//

// programa cliente6.cpp --> ler uma estrutura e utiliza o hostnome


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <netdb.h>


using std::cout;
using std::endl;

int main( )
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    
    unsigned short porta;
    struct hostent *nome_da_maquina;
    
    char hostname[256];
    
    struct dado {
        int idade;
        char nome[34];
    };
    
    
    dado pessoa1;
    porta = 9734;  // numero da porta
    
    strcpy(hostname, "NOME-DA-SUA-MAQUINA");
    nome_da_maquina = gethostbyname(hostname);  // pegando a m�quina a ser conectada
    if (nome_da_maquina == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname falhou\n");
        exit(2);
    }
    
    
    sockfd  = socket(AF_INET, SOCK_STREAM,0);  // criacao do socket
    
    address.sin_family = AF_INET;
    address.sin_addr = *(struct in_addr *) *nome_da_maquina->h_addr_list;
    // address.sin_addr.s_addr = *((unsigned long int *)nome_da_maquina->h_addr);
    // address.sin_addr.s_addr = *((unsigned long int *)nome_da_maquina->h_addr_list[0]);
    
    address.sin_port = htons(porta);
    
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *) &address, len);
    
    if (result == -1)
    {
        perror ("Houve erro no cliente");
        exit(1);
    }
    
    // write(sockfd,  pessoa1,sizeof(pessoa1));
    read(sockfd, &pessoa1,sizeof(pessoa1));
    
    cout << " nome : " << pessoa1.nome << endl;
    cout << " idade : " << pessoa1.idade <<endl;
    
    close(sockfd);
    exit(0);
}

