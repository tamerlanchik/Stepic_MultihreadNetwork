

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char* IN_CHAN = "/home/ian/in.fifo";
const char* OUT_CHAN = "/home/ian/out.fifo";

int loop(const int in_fifo, const int out_fifo) {
	char buffer[1024];
	int read_len = 0;
	for(;;) {
		if((read_len = read(in_fifo, buffer, sizeof(buffer)-1)) == (-1) && errno != EAGAIN) {
			perror("Cannot read");
			return -1;
		} else if (read_len <= 0) {
			continue;
		}
//		printf("Got data: %s\n", buffer);
		if(-1 == write(out_fifo, buffer, read_len)) {
			perror("Cannot write");
			return -1;
		}
	}
}

int main() {
	setbuf(stdout, 0);
	if (-1 == mkfifo(IN_CHAN, 0666)) {
		perror("Cannot create in.fifo");
//		return -1;
	}
	if (-1 == mkfifo(OUT_CHAN, 0666)) {
		perror("Cannot create out.fifo");
//		return -1;
	}

	int in_fifo = open(IN_CHAN, O_RDONLY | O_NONBLOCK);
	int out_fifo = open(OUT_CHAN, O_WRONLY);

	if (in_fifo==-1 || out_fifo == -1) {
		perror("Cannot open one of the chans");
		return -1;
	}

	int res = loop(in_fifo, out_fifo);
	if (res == -1) {
		perror("Error during loop");
	}
	close(in_fifo);
	close(out_fifo);
	return res;
}