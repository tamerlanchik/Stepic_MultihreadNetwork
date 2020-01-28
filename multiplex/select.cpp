#include <iostream>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>
#include <algorithm>
#include <unordered_set>

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

	while(true) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(master_socket, &set);

		for (auto iter = slave_sockets.begin(); iter != slave_sockets.end(); iter++) {
			FD_SET(*iter, &set);
		}

		auto m = std::max_element(slave_sockets.begin(), slave_sockets.end());
		int max = std::max(master_socket, (m==slave_sockets.end() ? master_socket : *m));
		select(max+1, &set, NULL, NULL, NULL);

		for (auto iter = slave_sockets.begin(); iter != slave_sockets.end(); iter++) {
			if(FD_ISSET(*iter, &set)) {
				static char buffer[1024];
				int recv_size = recv(*iter, buffer, sizeof(buffer), MSG_NOSIGNAL);
				if (recv_size == 0 && errno != EAGAIN) {
					printf("CLose socket %d\n", *iter);
					shutdown(*iter, SHUT_RDWR);
					close(*iter);
					slave_sockets.erase(iter);
				} else if(recv_size != 0) {
					printf("Got data on %d socket: %s\n", *iter, buffer);
					send(*iter, buffer, recv_size, MSG_NOSIGNAL);
				}

			}
		}

		if(FD_ISSET(master_socket, &set)) {
			int slave_socket = accept(master_socket, 0, 0);
			set_nonblock(slave_socket);
			slave_sockets.insert(slave_socket);
			printf("New socket: %d\n", slave_socket);
		}
	}


}

