
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>

size_t strcnt(const char* str, const char* substr) {
	int len = strlen(substr);
	size_t count = 0;
	const char* where = str;

	while(where = strstr(where, substr)) {
		++count;
		where += len;
	}
	return count;
}

int execute(const char* command, const char* args[], const int fd_in, const int fd_out) {
	int pid;
	if (pid = fork(), !pid) {
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
//		close(fd_in);
//		close(fd_out);
//		int res = execvp(command, args);
		exit(execvp(command, args));
		return 0;
	}
	return pid;
}

char** split(const char* str, const char* delim) {
	int words = strcnt(str, delim) + 1;
	if (words == 0) {
		return 0;
	}

	char **comm_batch = malloc(sizeof(char*)*(words+1));
	char* temp = malloc((strlen(str) + 1)*sizeof(char));
	strcpy(temp, str);
	char* temp2 = temp;
	size_t real_size = 0;
	for(size_t i = 0; i < words; ++i) {
		char* token = strtok(temp2, delim);
		if (!token) {
			continue;
		}
		temp2 = NULL;
		comm_batch[real_size] = malloc(sizeof(char)*strlen(token));
		strcpy(comm_batch[real_size], token);
		++real_size;
	}
	free(temp);
	comm_batch[real_size] = NULL;
	return comm_batch;
}

size_t arrlen(const void** src) {
	size_t len = 0;
	while(*src) {
		++len;
		src++;
	}
	return len;
}

int main() {

	char command[255];
	int n = read(STDIN_FILENO, command, sizeof(command));
	command[n-1] = '\0';

	char** pipe_batch = split(command, "|");
	const size_t pipe_len = arrlen((const void**)pipe_batch);

	int fd_entre;
	const int PIPE_IN = 1;
	const int PIPE_OUT = 0;
	fd_entre = dup(STDIN_FILENO);
	int fd[2];
	for(size_t i = 0; i < pipe_len; i++) {
		char** comm = split(pipe_batch[i], " ");
		if(i < pipe_len-1) {	// main process
			printf("A\n");
			if (pipe(fd) < 0) {
				perror("Cannot create pipe");
				return -1;
			}
			printf("New pipe: %d<-%d\n", fd[PIPE_OUT], fd[PIPE_IN]);
		} else {	// end
			fd[PIPE_IN] = open("/home/box/result.out", O_RDWR | O_TRUNC | O_CREAT, 0666);;
			printf("B\n");
		}

//		printf("Contacts: from %d to %d\n", fd_entre, fd[PIPE_IN]);
		arrlen(comm);

		int res = execute(comm[0], (const char**)comm, fd_entre, fd[PIPE_IN]);
		if (res == 0) {
			return 0;
		}
		wait(NULL);
		close(fd[PIPE_IN]);
		close(fd_entre);
//		printf("Res%ld: %d\n", i, res);

		fd_entre = fd[PIPE_OUT];
	}

	wait(NULL);
//	printf("Res: %d\n", 0);
	return 0;
}