#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

const unsigned int WORKER_COUNT = 100;
const char* PIPE_PATHNAME = "/home/ian/pipe";
const int ERROR = -1;


int create_worker(const int fd, const int quit_chan, const unsigned int number) {
	int pid;
	if( (pid = fork()) > 0) {
		return pid;
	}

	char buffer[1024];
	printf("Worker #%d started!\n", number);
	for(;;) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd, &set);
		FD_SET(quit_chan, &set);

		select((fd > quit_chan ? fd : quit_chan) + 1, &set, NULL, NULL, NULL);
		printf("Select worker #%ld\n", number);

		if(FD_ISSET(quit_chan, &set)) {
			printf("Worker #%ld quiting...\n", number);
			return 0;
		}

		int len = read(fd, buffer, 1024);
		if (len == ERROR) {
			printf("Cannot read in worker #%ld\n", number);
			perror("");
			return ERROR;
		} else if(len == 0) {
			continue;
		}
		printf("#%ld: %s\n", number, buffer);
	}

}

int dispatcher(const char* data_chan, const int worker_count, const int quit_chan) {
	int pid;
	if (pid = fork()) {
		return pid;
	}

	int worker_datachans[worker_count];

	for(unsigned int i = 0; i < WORKER_COUNT; ++i) {
		int fd[2];
		if (ERROR == pipe(fd)) {
			perror("Cannot create pipe");
			return ERROR;
		}
		worker_datachans[i] = fd[1];
		int res = create_worker(fd[0], quit_chan, i);
		if (res < 0) {
			perror("Error during creating worker");
			return ERROR;
		} else if(res == 0) {
			exit(0);
		}
	}

	int fd = open(data_chan, O_RDONLY);
	if (fd == ERROR) {
		perror("Error during opening datachan in dispatcher");
		return ERROR;
	}
	char buffer[1024];
	srand(time(NULL));

	for(;;) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd, &set);
		FD_SET(quit_chan, &set);
		select(1 + (fd > quit_chan ? fd : quit_chan), &set, NULL, NULL, NULL);
		if(FD_ISSET(quit_chan, &set)) {
			printf("Dispatcher quiting...");
			exit(0);
		}


		int len = read(fd, buffer, 1024);
		if (len == 0) {
			continue;
		} else if(len == ERROR) {
			perror("Error during read from datachan");
			return ERROR;
		}

		int n = rand() % worker_count;
		if(ERROR == write(worker_datachans[n], buffer, len)) {
			printf("Cannot write data to chan %d\n", n);
			perror("");
			return ERROR;
		}

	}

}


const int PIPE_READ = 0;
const int PIPE_WRITE = 1;

void on_quit(int t) {
	static int fd = -1;
	if (fd == -1) {
		fd = t;
		return;
	}
	if (fd > 0) {
		printf("Terminating...");
			if (ERROR == write(fd, "quit", 5)) {
				perror("Cannot write quit");
			} else {
				printf("Wrote quit");
			}
		wait(NULL);
	}
}
int main(int argc, const char* argv[]) {
    setbuf(stdout, 0);
    if(mkfifo(PIPE_PATHNAME, 0666) == ERROR && errno != EEXIST) {
    	printf("Cannot create channel: %d\n", errno);
    	return ERROR;
    }

	struct Quit {
    	const char* command;
		int quit_chan[2];
		void (*callback) (int);
	};
    struct Quit quit = {"quit", {0, 0}, &on_quit};
    if(ERROR == pipe(quit.quit_chan)) {
    	perror("Cannot creae quit chan");
    	return ERROR;
    }
    //	set internal static variable;
    quit.callback(quit.quit_chan[PIPE_WRITE]);

    dispatcher(PIPE_PATHNAME, WORKER_COUNT, quit.quit_chan[PIPE_READ]);

	if (SIG_ERR == signal(SIGINT, &on_quit)) {
		perror("Cannot set SIGINT");
		return ERROR;
	}

    int fd = open(PIPE_PATHNAME, O_WRONLY);
    if (fd == ERROR) {
    	perror("Cannot open chan for write");
    	return ERROR;
    }

    char buffer[1024];
    const char* quit_command = "quit";
    for(;;) {
    	printf("$>");
    	scanf("%1023s", buffer);
    	int len = strlen(buffer);
    	if (len <= 0) {
			printf("Wrong string\n");
			continue;
    	}
    	if (!strcmp(quit_command, buffer)) {
			quit.callback(0);
			break;
    	}
		if (ERROR == write(fd, buffer, len+1)) {
			printf("Cannot write\n");
			continue;
		}
    }

	wait(NULL);




    return 0;
}