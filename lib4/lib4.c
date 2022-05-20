#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define READ_END    0
#define WRITE_END   1
#define BUFFER_SIZE 100

int main() {
    int fd[2];
    if (pipe(fd) == -1 ){
        puts("Create pipe failed");
        exit(-1);
    }
    pid_t pid = fork();
    if (pid < 0) {
       puts("Fork failed");
       exit(pid);
    }
    else if (pid > 0) {
        printf("Parent process started! PID = %u\n", getpid());
        close(fd[READ_END]);
        char write_msg[BUFFER_SIZE] = "Hello, pipe!";
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("Write data: %s\n", write_msg);
        close(fd[WRITE_END]);
        sleep(2);
        puts("Parent process exited!");
    }
    else {
        printf("Child process started! PID = %u\n", getpid());
        close(fd[WRITE_END]);
        sleep(1);
        char read_msg[BUFFER_SIZE];
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Read data: %s\n", read_msg);
        close(fd[READ_END]);
        puts("Child process exited!");
    }
    return 0;
}