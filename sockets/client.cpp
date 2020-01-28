//
// Created by Ian on 27.01.2020.
//
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {
	int socket_main = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_main == -1) {
		std::cerr << "Error open socket!\n";
		return -1;
	}

	struct sockaddr_in sock_addr;
	sock_addr.sin_port =htons(12345);
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (connect(socket_main, (struct sockaddr*)(&sock_addr), sizeof(sock_addr)) == -1) {
		std::cerr << "Error connect!\n";
		close(socket_main);
		return -1;
	}

	char buffer[] = "PING";

	send(socket_main, buffer, sizeof(buffer), MSG_NOSIGNAL);
	recv(socket_main, buffer, sizeof(buffer), MSG_NOSIGNAL);

	shutdown(socket_main, SHUT_RDWR);
	close(socket_main);

	printf("Got: %s\n", buffer);
	return 0;

}

