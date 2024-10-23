//
//  servidor4.cpp
//  
//
//  Created by Affonso on 25/04/16.
//
//

// programa servidor4.cpp - Servidor que l� e escreve em um vetor de caracter

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char** argv) {
    int s_sockfd, c_sockfd;
    sockaddr_in s_addr;
    sockaddr_in c_addr;
    socklen_t c_len = sizeof(c_addr);

	unsigned char message[65507];
    
    //unlink("server_socket");  // remocao de socket antigo
    s_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // cria um novo socket
    
    s_addr.sin_family = AF_INET;
    //s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(9734);
    
    //strcpy(s_addr.sun_path, "server_socket");
    
    bind(s_sockfd, (sockaddr*)&s_addr, sizeof(s_addr));
    
    while(true) {
        std::cout << "Servidor escutando ...\n";
        size_t size = recvfrom(s_sockfd, message, sizeof(message), 0, (sockaddr*)&c_addr, &c_len);
        sendto(s_sockfd, message, size, 0, (sockaddr*)&c_addr, c_len);
    }

    close(s_sockfd);
    return 0;
}

