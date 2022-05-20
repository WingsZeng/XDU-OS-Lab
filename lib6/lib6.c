#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

sem_t mutex, empty, full;
int item_buf[100], top = 0;

void *producer(void *arg) {
    int id = 0;
    puts("Producer started!");
    while (true) {
        sleep(2);
        sem_wait(&empty);
        sem_wait(&mutex);
        item_buf[top++] = id;
        printf("Produced %d\n", id++);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer_a(void *arg) {
    sleep(15);
    puts("Consumer A started!");
    while (true) {
        sem_wait(&full);
        sem_wait(&mutex);
        int id = item_buf[--top];
        printf("Consumer A consumed %d\n", id);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(3);
    }
}

void *consumer_b(void *arg) {
    sleep(20);
    puts("Consumer B started!");
    while (true) {
        sem_wait(&full);
        sem_wait(&mutex);
        int id = item_buf[--top];
        printf("Consumer B consumed %d\n", id);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_t tid_ca, tid_cb, tid_p;
    pthread_create(&tid_p, NULL, producer, NULL);
    pthread_create(&tid_ca, NULL, consumer_a, NULL);
    pthread_create(&tid_cb, NULL, consumer_b, NULL);
    sleep(30);
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}