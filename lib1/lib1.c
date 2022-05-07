#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork error %d\n", pid);
		exit(pid);
	}
	else if (pid == 0) {
		printf("Child process started! PID = %d\n", getpid());
		freopen("./data", "r", stdin);
		puts("Child read file:");
		char buf[205];
		int n;
		while ((n = read(0, buf, 200)) > 0)
			write(1, buf, n);
		puts("Child process will exit in 2 seconds!");
		sleep(2);
	}
	else {
		printf("Father process started! PID = %d\n", getpid());
		puts("Wait for child process...");
		int status;
		waitpid(pid, &status, 0);
		puts("Child process exited!");
		puts("Father process will exit in 2 seconds!");
		sleep(2);
	}
	return 0;
}