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
#include <arpa/inet.h>
#include <functional>

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

class ChatUser{
private:
	unsigned int _id;
	std::string _ip;
public:
	ChatUser(const unsigned int id, const std::string& ip) : _id(id), _ip(ip) {}
	static bool compareById(const ChatUser a, const ChatUser& b) {
		return a._id < b._id;
	}

	static std::function<bool (const ChatUser&, const ChatUser&)> comparator() {
		return [](const ChatUser& a, const ChatUser& b) -> bool{
			return a._id < b._id;
		};
	}
	struct Compare{
		bool operator()(const ChatUser& a, const ChatUser& b) {
			return a._id < b._id;
		}
	};

	std::string GetIp() const {
		return _ip;
	}

	unsigned int GetId() const {
		return _id;
	}
};

class Chat {
private:
	std::set<ChatUser, ChatUser::Compare> _users;
	int (*_send_callback)(unsigned int, const char*, const size_t size);

public:
	Chat() {}
	void AddUser(const std::string& ip, const unsigned int id) {
		_users.insert(ChatUser(id, ip));
		onAddUser(ip);
	}

	void RemoveUser(const unsigned int id) {
		auto iter = _users.find(ChatUser(id, ""));
		if (iter == _users.end()) {
			return;
		}
		ChatUser user = *iter;
		_users.erase(user);
		onDeleteUser(user.GetIp());
	}

	void NewBroadcastMessage(const char* buffer, const size_t size, const unsigned int id) {
		std::for_each(_users.cbegin(), _users.cend(), [buffer, size, id, this](ChatUser user) {
			if (user.GetId() == id) return;
			std::string ip = user.GetIp();
			std::string message = ip + ": " + std::string(buffer);
			_send_callback(user.GetId(), message.c_str(), message.size());
		});
	}

	void onAddUser(const std::string ip) {
		for(auto iter = _users.cbegin(); iter != _users.cend(); iter++) {
			std::string message = "New user " + (*iter).GetIp() + "\n";
			int res = _send_callback((*iter).GetId(), message.c_str(), message.size());
			if (res == -1) {
				std::cerr << "Cannot send message\n";
			}
		}
	}

	void onDeleteUser(const std::string ip) {
		for(auto iter = _users.cbegin(); iter != _users.cend(); iter++) {
			std::string message = "User " + (*iter).GetIp() + " deleted\n";
			int res = _send_callback((*iter).GetId(), message.c_str(), message.size());
			if (res == -1) {
				std::cerr << "Cannot send message\n";
			}
		}
	}

	void AddSendCallback(int (*send_callback)(unsigned int, const char*, const size_t)) {
		_send_callback = send_callback;
	}

};

class ChatServer {
private:
	const int MAX_EVENT = 32;
	Chat* _chat;
public:
	ChatServer(const std::string& address, const unsigned int port) {
		int res = init(address.c_str(), port);
		if (res != 0) {
			throw("Cannot init server");
		}
		_chat = new Chat();
		_chat->AddSendCallback(ChatServer::send);
	}

	~ChatServer() {
		shutdown(_master_socket, SHUT_RDWR);
		close(_master_socket);
		close(_epoll);
	}

	int Run() {
		std::cout << "Server running...\n";
		while(true) {
			this->run_epoll();
		}
	}

	std::string GetError() const {
		return _error;
	}
private:
	int _master_socket;
	std::string _error;
	int _epoll;

	int init(const char* address, const unsigned int port) {
		_master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_master_socket == -1) {
			_error = "Cannot init master socket!";
			return _master_socket;
		}
		struct sockaddr_in sock_addr;
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_port = htons(port);
		sock_addr.sin_addr.s_addr = inet_addr(address);

		if (-1 == bind(_master_socket, (struct sockaddr*)(&sock_addr), sizeof(sock_addr))) {
			_error = "Cannot bind master socket.";
			return _master_socket;
		}
		if(-1 == set_nonblock(_master_socket)) {
			_error = "Cannot set nonblock master socket";
			return -1;
		}

		if (-1 == listen(_master_socket, SOMAXCONN)) {
			_error = "Cannot start listeting master socket.";
			return _master_socket;
		}

		int res = init_epoll();
		if (res != 0) {
			_error = "Cannot init epoll";
		}
		return res;
	}

	int init_epoll() {
		_epoll = epoll_create1(0);
		struct epoll_event event;
		event.data.fd = _master_socket;
		event.events = EPOLLIN;
		return epoll_ctl(_epoll, EPOLL_CTL_ADD, _master_socket, &event);
	}

	int run_epoll() {
		epoll_event events[MAX_EVENTS];
		int n = epoll_wait(_epoll, events, MAX_EVENTS, -1 /*endless*/);
		if (n == -1) {
			_error = "Error in epoll_wait()";
			return -1;
		}
		int res;
		for(unsigned int i = 0; i < n; i++) {
			res = this->handle_epoll_event(events[i]);
			if (res == -1) {
				return res;
			}
		}
	}

	int handle_epoll_event(const epoll_event& event) {
		if(event.data.fd == _master_socket) {
			return this->accept_new_connection(_master_socket);
		} else {
			return this->receive_data(event);
		}
	}

	int accept_new_connection(const int socket) {
		sockaddr_in from_addr;
		socklen_t len = sizeof(sockaddr_in);
		int slave_socket = accept(socket, (sockaddr *)&from_addr, &len);

		if (slave_socket == -1) {
			_error = "Cannot accept new connection!\n";
			return -1;
		}
		set_nonblock(slave_socket);

		struct epoll_event event;
		event.data.fd = slave_socket;
		event.events = EPOLLIN;
		int res = epoll_ctl(_epoll, EPOLL_CTL_ADD, slave_socket, &event);
		if (res == -1) {
			_error = "Error in epoll_ctl adding slave socket";
			return -1;
		}
		printf("New socket: %d\n", slave_socket);

		std::string incom_addr = std::string(inet_ntoa(from_addr.sin_addr));
		_chat->AddUser(incom_addr, slave_socket);
	}

	static int send(const unsigned int fd, const char* data, const size_t size) {
		return ::send(fd, data, size, MSG_NOSIGNAL);
	}

	int receive_data(const epoll_event& event) {
		static char buffer[1024];
		int res = recv(event.data.fd, buffer, 1024, MSG_NOSIGNAL);
		if (res == -1) {
			_error = "error in recv data from socket";
			return -1;
		}
		buffer[res] = '\0';
		if (res==0 && errno != EAGAIN) {
			return close_socket(event.data.fd);
		} else if (res > 0) {
			printf("Got data on %d socket: %s\n", event.data.fd, buffer);
			_chat->NewBroadcastMessage(buffer, res, event.data.fd);
//			res = ::send(event.data.fd, buffer, res, MSG_NOSIGNAL);
//			if (res == -1) {
//				_error = "Error sending data";
//				return -1;
//			}
		}
		return 0;
	}

	int close_socket(const int fd) {
		int res = shutdown(fd, SHUT_RDWR);
		if (res == -1) {
			_error = "Error in shutdown() on slave socket";
			return -1;
		}
		res = close(fd);
		if (res == -1) {
			_error = "Error in close slave socket";
			return -1;
		}
		printf("CLose socket %d\n", fd);
		_chat->RemoveUser(fd);
		return 0;
	}

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
};

int main(int argc, char** argv) {
	ChatServer* server = nullptr;
	try{
		server = new ChatServer("0.0.0.0", 12345);
	} catch (std::exception e) {
		std::cerr << "Init exception";
		return -1;
	} catch (char const* e){
		std::cerr << server->GetError();
		return -1;
	}
	std::cout << "Server inited\n";
	int res = server->Run();
	std::cerr << "Exit status: " << res << std::endl;
	return res;
}

