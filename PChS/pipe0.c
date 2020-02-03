#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	int fd[2], fd2[2];
	const int PIPE_READ = 0;
	const int PIPE_WRITE = 1;
	if(pipe(fd) == -1) {
		perror("Cannot create pipe");
		return -1;
	}
	if(pipe(fd2) == -1) {
		perror("Cannot create pipe2");
		return -1;
	}

	for(int i = 0; i < 10; i++) {
		int fd3[2];
		pipe(fd3);
		printf("Pipe3: %d <- %d\n", fd3[0], fd3[1]);
	}
	printf("Pipe1: %d <- %d\n", fd[0], fd[1]);
	printf("Pipe2: %d <- %d\n", fd2[0], fd2[1]);
	int pid;
	if (pid = fork(), pid == -1) {
		perror("Cannot fork");
		return -1;
	} else if(pid == 0){
		//	child
		char buf[10];
//		close(fd[0]);
		if(!fork()) {
			if(-1 == read(fd2[PIPE_READ], buf, sizeof(buf))) {
				perror("Cannot read");
				return -1;
			}
			printf("Got2: %s\n", buf);
			return 0;
		}
		if(-1 == read(fd[PIPE_READ], buf, sizeof(buf))) {
			perror("Cannot read");
			return -1;
		}
		printf("Got: %s\n", buf);
		if (-1 ==write(fd2[PIPE_WRITE], "Fuckoff", 8) ) {
			perror("Canot write to pipe2");
			return -1;
		}
	}
//	close(fd[1]);
	if (-1 == write(fd[PIPE_WRITE], "Hello", 6)) {
		perror("Cannot write");
		return -1;
	}
	wait(NULL);
	return 0;
}
