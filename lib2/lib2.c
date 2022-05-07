#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

char shared_data[100];

void *thread_fun(void *arg) {
	printf("Thread started! Thread ID = %lu\n", pthread_self());
	strcpy(shared_data, "thread");
	puts("Shared data changed in thread!");
	puts("Thread ended!");
}

int main() {
	printf("Main process started! Process PID = %u\n", getpid());
	strcpy(shared_data, "main");
	printf("Shared data is \'%s\' now\n", shared_data);
	pthread_t tid;
	unsigned int err_code = pthread_create(&tid, NULL, thread_fun, NULL);
	if (err_code) {
		fprintf(stderr, "Thread create error: %u\n", err_code);
		exit(err_code);
	}
	sleep(1);
	printf("Shared data is \'%s\' now\n", shared_data);
	puts("Main process ended!");
	return 0;
}