#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
	puts("Received SIGINT signal!");
}

int main() {
	pid_t pid = fork();
	if (pid == 0) {
		printf("Child process started! PID = %u\n", getpid());
		sleep(1);
		printf("After sleep one second, child process PID = %u\n", getpid());
		sleep(1);
		printf("After sleep two seconds, child process PID = %u\n", getpid());
		exit(0);
	}
	else if (pid > 0) {
		printf("Parent process started! PID = %u\n", getpid());
		signal(SIGINT, handler);
		pause();
	}
	else {
		fprintf(stderr, "Fork error: %d\n", pid);
		exit(pid);
	}
	return 0;
}