#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

const int ERR = -1;

int main(int argc, char** argv) {
	std::cout << "Start!\n";

	int main_socket = socket(
			AF_INET,
			SOCK_STREAM,
			IPPROTO_TCP
			);
	if (main_socket == ERR) {
		std::cerr << "Error init socket\n";
		return ERR;
	}
	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 0.0.0.0

	int stat = bind(main_socket, (sockaddr *)(&sock_addr), sizeof(sock_addr));
	if (stat == ERR) {
		std::cerr << "Error bind socket\n";
		return ERR;
	}

	if (listen(main_socket, SOMAXCONN) == ERR) {
		std::cerr << "Error start listening socket\n";
		return ERR;
	}
	while(true) {
		int slave_socket = accept(main_socket, 0, 0);
		if (slave_socket == -1) {
			std::cerr << "Error accept!\n";
			continue;
		}
		printf("New slave socket: %d\n", slave_socket);
		char buffer[5] = {0, 0, 0, 0, 0};
		ssize_t read = recv(slave_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
		if (read ==-1) {
			std::cerr << "Error in recv!\n";
			shutdown(slave_socket, SHUT_RDWR);
			close(slave_socket);
			continue;
		}
		printf("Read %d bytes\n", read);
		char buffer2[] = "PONG";
		if (send(slave_socket, buffer2, sizeof(buffer2), MSG_NOSIGNAL) == -1) {
			std::cerr << "Cannot send\n";
		}
		shutdown(slave_socket, SHUT_RDWR);
		close(slave_socket);
		printf("Got: %s\n", buffer);
	}

	return 0;
}