#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int ERROR = -1;
int main(int argc, const char* argv[]) {
	const int PIPE_READ = 0;
	const int PIPE_WRITE = 1;
	int fd[2];
	if (ERROR == socketpair(AF_UNIX, SOCK_STREAM, 0, fd)) {
		perror("Cannot create socketpair");
		return ERROR;
	}
	if (!fork()) {
		close(fd[PIPE_WRITE]);
		char buffer[1024];
		for(;;) {
			int len = read(fd[PIPE_READ], buffer, 1024);
			if (len == -1) {
				perror("Cannot read");
				return -1;
			} else if(len == 0) {
				continue;
			}
			printf("%s\n", buffer);
		}
		return 0;
	}

	char buffer[1024];

	for(;;) {
		int len = scanf("%s", buffer);
		int res = write(fd[PIPE_WRITE], buffer, strlen(buffer)+1);
		if (res == -1) {
			perror("Cannot write");
			return -1;
		}
	}

	return 0;
}