#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <fmt/core.h>

int main(int argc, char** argv) {
	if (argc < 3 || argc > 4) {
		std::cout << "uso: ./net_time.exe <num-de-bytes> <IP>\n";
		return 0;
	}

	// pegar a quantidade de bytes a ser enviada
	const int num_bytes = strtol(argv[1], nullptr, 10);

	std::cout << num_bytes << '\n';

	if (num_bytes <= 0) {
		std::cout << "A quantidade de bytes a ser enviada deve ser um numero positivo\n";
		return -1;
	}

	// preencher o vetor de mensagem
	unsigned char message[num_bytes];
	srand(time(nullptr));
	message[0] = rand() % 256;
	#ifdef PRINT
	std::cout << '[' << (unsigned int)message[0];
	#endif
	for (int i = 1; i < num_bytes; i++) {
		message[i] = rand() % 256;
		#ifdef PRINT
		std::cout << ", " << (unsigned int)message[i];
		#endif
	}
	#ifdef PRINT
	std::cout << "]\n";
	#endif

	// criar socket para fazer loopback
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		std::cout << "Falha na criação do socket.\n";
		return -1;
	}

	sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr("172.0.0.1");
	s_addr.sin_port = htons(9734);

	socklen_t s_addr_len;

	// fazer envio e recebimento da mensagem de loopback
	timeval start, finish;
	gettimeofday(&start, nullptr);
	sendto(sockfd, message, sizeof(message), 0, (sockaddr*)&s_addr, sizeof(s_addr));
	ssize_t size = recvfrom(sockfd, message, sizeof(message), 0, (sockaddr*)&s_addr, &s_addr_len);
	gettimeofday(&finish, nullptr);
	std::cout << size << '\n';

	// calculat o tempo de loopback	
	double loopback_time = /*(finish.tv_sec - start.tv_sec)*1000.0 + */ (finish.tv_usec - start.tv_usec)/1000.0;

	fmt::print("Tempo de loopback: {:.4f} ms.\n", loopback_time);
	
	// fechar a conexao
	close(sockfd);
	
	// // abrir uma nova conexao
	// sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// if (sockfd == -1) {
	// 	std::cout << "Falha na criação do socket.\n";
	// 	return -1;
	// }

	// s_addr.sin_family = AF_INET;
	// s_addr.sin_addr.s_addr = inet_addr(argv[2]);
	// s_addr.sin_port = htons(9734);

	// // fazer envio e recebimento da mensagem para a outra maquina
	// gettimeofday(&start, nullptr);
	// sendto(sockfd, message, sizeof(message), 0, (sockaddr*)&s_addr, sizeof(s_addr));
	// recvfrom(sockfd, message, sizeof(message), 0, (sockaddr*)&s_addr, &s_addr_len);
	// gettimeofday(&finish, nullptr);

	// // calcular o tempo total	
	// double total_time = (finish.tv_sec - start.tv_sec)*1000.0 + (finish.tv_usec - start.tv_usec)/1000.0;

	// fmt::print("Tempo de total: {:.4f} ms.\n", total_time);
	
	// // fechar a conexao
	// close(sockfd);
	
	// // calcular o tempo de rede
	// fmt::print("Tempo de rede: {:.4f} ms\n", total_time - 2*loopback_time);

	return 0;
}