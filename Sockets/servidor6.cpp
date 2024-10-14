//
//  servidor6.cpp
//  
//
//  Created by Affonso on 25/04/16.
//
//

// programa servidor6.cpp - Servidor utilizando o hostname


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main( )
{
    int server_sockfd, client_sockfd;
    size_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    unsigned short porta = 9734;
    
    
    //unlink("server_socket");  // remocao de socket antigo
    if ( (server_sockfd = socket(AF_INET, SOCK_STREAM, 0) )  < 0  )  // cria um novo socket
    {
        printf(" Houve erro na ebertura do socket ");
        exit(1);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(porta);
    
    
    
    server_len = sizeof(server_address);
    
    if(  bind(server_sockfd, (struct sockaddr *) &server_address, server_len) < 0 )
    {
        perror("Houve error no Bind");
        exit(1);
    }
    
    if (listen(server_sockfd, 5) != 0)
    {
        perror("Houve error no Listen");
        exit(1);
    }
    
    while(1) {
        
        struct dado {
            int idade;
            char nome[34];
        };
        
        dado aluno;
        aluno.idade = 38;
        strcpy(aluno.nome, "Jose Silva");
        
        printf("Servidor esperando ...\n");
        
        if( client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) &client_len) < 0)
        {
            perror("Houve erro no Accept");
            exit(2);
        }
        
        printf(" O Cliente %d se conectou ao servidor \n", client_sockfd);
        
        if( write(client_sockfd, &aluno, sizeof(aluno)) < 0 )
        {
            perror("Houve erro na escrita WRITE()");
            exit(3);
        }
        
        printf(" O Servidor executou o WRITE\n" );
        close(client_sockfd);
    }
}

