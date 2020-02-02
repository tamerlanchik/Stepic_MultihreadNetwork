#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

void who_vc() {
	int pfd[2];
	if (-1 == pipe(pfd)) {
		std::cerr << "Pipe() returned error\n";
		return;
	}

	if (!fork()) {
		//	Child
		close(STDERR_FILENO);
		if (-1 == dup2(pfd[1], STDOUT_FILENO)) {
			std::cerr << "child dup2() returned error\n";
			return;
		}
		close(pfd[0]);
		close(pfd[1]);
		if (0 != execlp("pwd", "pwd", NULL)) {
			std::cerr << "child execlp() returned error\n";
			return;
		}

	} else {
		// Parent
		close(STDIN_FILENO);
		if (0 != dup2(pfd[0], STDIN_FILENO)) {
			std::cerr << "parent dup2() returned error\n";
			return;
		}
		close(pfd[0]);
		close(pfd[1]);
		if (0 != execlp("wc", "wc", "-l", NULL)) {
			std::cerr << "parent execlp() returned error\n";
			return;
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	wait(NULL);
	wait(NULL);

}

int main(int argc, char** argv) {
	who_vc();
	return 0;
}
