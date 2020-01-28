#include <iostream>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <sys/epoll.h>

const int MAX_EVENTS = 32;

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
	int res = set_nonblock(master_socket);

	if (-1 == listen(master_socket, SOMAXCONN)) {
		std::cerr << "Cannot start listeting master socket. Terminating...\n";
		return master_socket;
	}

	int epoll = epoll_create1(0);
	struct epoll_event event;
	event.data.fd = master_socket;
	event.events = EPOLLIN;
	epoll_ctl(epoll, EPOLL_CTL_ADD, master_socket, &event);



	while(true) {
		struct epoll_event events[MAX_EVENTS];
		int n = epoll_wait(epoll, events, MAX_EVENTS, -1 /*endless*/);
		printf("Epoll returned n=%d\n", n);
		for(unsigned int i = 0; i < n; i++) {
			if(events[i].data.fd == master_socket) {
				int slave_socket = accept(master_socket, 0, 0);
				if (slave_socket == -1) {
					std::cerr << "Cannot accept new connection!\n";
					exit(1);
				}
				set_nonblock(slave_socket);

				struct epoll_event event;
				event.data.fd = slave_socket;
				event.events = EPOLLIN;
				epoll_ctl(epoll, EPOLL_CTL_ADD, slave_socket, &event);
				printf("New socket: %d\n", slave_socket);
			} else {
				static char buffer[1024];
				int res = recv(events[i].data.fd, buffer, 1024, MSG_NOSIGNAL);
				buffer[res] = '\0';
				if (res==0 && errno != EAGAIN) {
					shutdown(events[i].data.fd, SHUT_RDWR);
					close(events[i].data.fd);
					printf("CLose socket %d\n", events[i].data.fd);
				} else if (res > 0) {
					printf("Got data on %d socket: %s\n", events[i].data.fd, buffer);
					send(events[i].data.fd, buffer, res, MSG_NOSIGNAL);
//					shutdown(events[i].data.fd, SHUT_RDWR);
//					close(events[i].data.fd);
				}
			}
		}

	}


}

