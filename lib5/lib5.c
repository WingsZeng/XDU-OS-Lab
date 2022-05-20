#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_SERVER "./fifoserver"
#define BUFFER_SIZE 100

int main() {
    if (mkfifo(FIFO_SERVER, 0664) == -1) {
        puts("Create fifo failed");
        exit(-1);
    }
    pid_t pid = fork();
    if (pid < 0) {
        puts("Fork failed");
        exit(pid);
    }
    if (pid > 0) {
        printf("Parent process started! PID = %u\n", getpid());
        sleep(1);
        int fd = open(FIFO_SERVER, O_RDONLY);
        char read_msg[BUFFER_SIZE];
        read(fd, read_msg, BUFFER_SIZE);
        printf("Parent read from fifo: %s\n", read_msg);
        close(fd);
        sleep(1);
        puts("Parent process exited!");
    }
    else {
        printf("Child process started! PID = %u\n", getpid());
        int fd = open(FIFO_SERVER, O_WRONLY);
        char write_msg[BUFFER_SIZE] = "Hello, fifo!";
        write(fd, write_msg, strlen(write_msg) + 1);
        printf("Child write to fifo: %s\n", write_msg);
        close(fd);
        puts("Child process exited!");
    }
    return 0;
}