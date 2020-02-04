#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

const unsigned int WORKER_COUNT = 2;
const char* PIPE_PATHNAME = "/home/ian/pipe";

int create_worker(const char* data_chan, const int quit_chan, const unsigned int number) {
	int pid;
	if( (pid = fork()) > 0) {
		return pid;
	}

	int fd = open(data_chan, O_RDONLY);
	if (fd == -1) {
		printf("Error during opening channel in worker #%ld\n", number);
		return -1;
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
		if (len == -1) {
			printf("Cannot read in worker #%ld\n", number);
			perror("");
			return -1;
		} else if(len == 0) {
			continue;
		}
		printf("#%ld: %s\n", number, buffer);
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
//		for(int i = 0; i < WORKER_COUNT; i++) {
int i = 0;
			if (-1 == write(fd, "quit", 5)) {
				printf("Cannot write quit #%ld\n", i);
				perror("");
			} else {
				printf("Wrote quit to #%ld\n", i);
			}
//		}
		wait(NULL);
	}
}
int main(int argc, const char* argv[]) {
    setbuf(stdout, 0);
    if(mkfifo(PIPE_PATHNAME, 0666) == -1 && errno != EEXIST) {
    	printf("Cannot create channel: %d\n", errno);
    	return -1;
    }

	struct Quit {
    	const char* command;
		int quit_chan[2];
		void (*callback) (int);
	};
    struct Quit quit = {"quit", {0, 0}, &on_quit};
    if(-1 == pipe(quit.quit_chan)) {
    	perror("Cannot creae quit chan");
    	return -1;
    }
    //	set internal static variable;
    quit.callback(quit.quit_chan[PIPE_WRITE]);


    for(unsigned int i = 0; i < WORKER_COUNT; ++i) {
		int res = create_worker(PIPE_PATHNAME, quit.quit_chan[PIPE_READ], i);
		if (res < 0) {
			perror("Error during creating worker");
			return -1;
		} else if(res == 0) {
			return 0;
		}
    }
	if (SIG_ERR == signal(SIGINT, &on_quit)) {
		perror("Cannot set SIGINT");
		return -1;
	}

    int fd = open(PIPE_PATHNAME, O_WRONLY);
    if (fd == -1) {
    	perror("Cannot open chan for write");
    	return -1;
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
    		break;
    	}
		if (-1 == write(fd, buffer, len+1)) {
			printf("Cannot write\n");
			continue;
		}
    }
    quit.callback(0);
//	printf("Start quiting...\n");
//	for(int i = 0; i < WORKER_COUNT; i++) {
//		if (-1 == write(quit_chan[PIPE_WRITE], "quit", 5)) {
//			printf("Cannot write quit #%ld\n", i);
//			perror("");
//		}
//	}
//	wait(NULL);




    return 0;
}