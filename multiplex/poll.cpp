#include <iostream>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <poll.h>

const int POLL_SIZE = 2048;

int set_nonblock(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	flags = 1;
	return ioctl(fd, FIOBIO, &flags)
#endif
}

int main(int argc, char** argv) {
	int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (master_socket == -1) {
		std::cerr << "Error creating main socket! Terminating...\n";
		return master_socket;
	}

	std::unordered_set<int> slave_sockets;
//	std::set<int> slave_sockets;
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (-1 == bind(master_socket, (struct sockaddr*)(&sock_addr), sizeof(sock_addr))) {
		std::cerr << "Cannot bind master socket. Terminating...\n";
		return master_socket;
	}
	set_nonblock(master_socket);

	if (-1 == listen(master_socket, SOMAXCONN)) {
		std::cerr << "Cannot start listeting master socket. Terminating...\n";
		return master_socket;
	}

	struct pollfd set[POLL_SIZE];
	set[0].fd = master_socket;
	set[0].events = POLLIN;		// Read only
	while(true) {
		unsigned int index = 1;
		for (auto iter = slave_sockets.begin(); iter != slave_sockets.end(); iter++) {
			set[index].fd = *iter;
			set[index].events = POLLIN;
			index++;
		}
		unsigned int set_size = 1 + slave_sockets.size();

		poll(set, set_size, -1); // endlessly await

		for(unsigned int i = 0; i < set_size; i++) {
			if (set[i].revents & POLLIN) {
				if (i != 0) {
					static char buffer[1024];
					int recv_size = recv(set[i].fd, buffer, 1024, MSG_NOSIGNAL);
					if (recv_size==0 && errno != EAGAIN) {
						printf("CLose socket %d\n", set[i].fd);
						shutdown(set[i].fd, SHUT_RDWR);
						close(set[i].fd);
						slave_sockets.erase(set[i].fd);
						continue;
					}
					printf("Got data on %d socket: %s\n", set[i].fd, buffer);
					send(set[i].fd, buffer, 1024, MSG_NOSIGNAL);
				} else {
					int slave_socket = accept(master_socket, 0, 0);
					set_nonblock(slave_socket);
					slave_sockets.insert(slave_socket);
					printf("New socket: %d\n", slave_socket);
				}
			}
		}
	}


}

