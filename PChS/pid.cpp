//#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <cstdio>

int main() {
	int pid = getpid();
	int fd = open("/home/ian/pid", O_WRONLY | O_CREAT);
//	FILE* fd = fopen("/home/box/pid", "w");
	if (fd < 0) {
		perror("Cannot create file pid");
		return -1;
	}
//	int n = write(fd, (const void*)&pid, sizeof(int));
//	if (-1 == n) {
//		perror("Cannot write to file");
//		return -1;
//	} else {
//		printf("%d bytes written\n", n);
//	}
	char s_pid[5];
	sprintf(s_pid, "%d", pid);
	printf("Pid: %d\n", pid);
	write(fd, (const void*)s_pid, sizeof(s_pid));
//	fprintf(fd, pid);
	if (-1 == close(fd)) {
		perror("Cannot close file");
		return -1;
	}

	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pause();
	return 0;

}
