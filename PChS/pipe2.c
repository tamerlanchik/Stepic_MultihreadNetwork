
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

int execute(const char* command, const char** args, const int fd) {
	if (!fork()) {
		int fd = open("/home/ian/fuck", O_RDWR | O_TRUNC | O_CREAT, 0666);
		close(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		printf("Execute %s...\n", command);
//		int res = execvp(command, args);
//		printf("Res2: %d\n", res);
		return execvp(command, args);
	}
	return 0;
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
	for(size_t i = 0; i < words; ++i) {
		char* token = strtok(temp2, delim);
		temp2 = NULL;
		comm_batch[i] = malloc(sizeof(char)*strlen(token));
		strcpy(comm_batch[i], token);
	}
	free(temp);
	comm_batch[words] = NULL;
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
	const size_t pipe_len = arrlen(pipe_batch);

	char** left_twix, right_twix;
	right_twix = split(pipe_batch[0], " ");
	int fd_end = open("/home/ian/fuck", O_RDWR | O_TRUNC | O_CREAT, 0666);
	for(size_t i = 0; i < pipe_len; i++) {
		char** comm = split(pipe_batch[i], " ");

		int res = execute(comm[0], comm, fd_end);
		printf("Res2: %d\n", res);
		wait(NULL);
	}
	char** command1 = split(pipe_batch[0], " ");
//	if (!fork()) {
//		char* new_command = strtok(command, " ");
//		int fd = open("/home/ian/fuck", O_RDWR | O_TRUNC | O_CREAT, 0666);
//		close(STDOUT_FILENO);
//		dup2(fd, STDOUT_FILENO);
//		close(fd);
//		int res = execvp(command1[0], command1);
//		printf("Res2: %d\n", res);
//		return 0;
//	}
	wait(NULL);

	printf("Res: %d\n", 0);
	return 0;
}