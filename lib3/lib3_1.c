#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig) {
	pid_t pid;
	int status;
	while (pid = waitpid(-1, &status, WNOHANG) > 0) {
		printf("Child process %d died: %d\n", pid, WEXITSTATUS(status));
		printf("Parent process received SIGCHLD signal!");
	}
}

int main() {
	pid_t pid = fork();
	if (pid == 0) {
		printf("Child process started! PID = %u\n", getpid());
		sleep(1);
		printf("After sleep one second, child process PID = %u\n", getpid());
		exit(0);
	}
	else if (pid > 0) {
		printf("Parent process started! PID = %u\n", getpid());
		signal(SIGCHLD, handler);
		sleep(2);
	}
	else {
		fprintf(stderr, "Fork error: %d\n", pid);
		exit(pid);
	}
	return 0;
}