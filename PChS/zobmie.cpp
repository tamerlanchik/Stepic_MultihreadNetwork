//
// Created by Ian on 01.02.2020.
//

#include <unistd.h>
#include <wait.h>
#include <fstream>

int main() {
	std::ofstream parent("/home/ian/pid_parent");
	parent << getpid();
	parent.close();
	if (!fork()) {
		//	child
		std::ofstream child("/home/ian/pid_child");
		child << getpid();
		child.close();
		signal(SIGTERM, SIG_DFL);
		pause();
		return 0;
	}
	int st;
	waitpid(-1, &st, 0);
	return 0;
}
