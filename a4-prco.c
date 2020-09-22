#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
void *thread_function(void *arg);

#define N 5

int buffer[N];
sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    sem_wait(&bin_sem);

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    sem_wait(&bin_sem);

    pthread_exit(NULL);
}

int main()
{
    int res;
    pthread_t prod, cons;
    void *thread_result;

    res = sem_init(&bin_sem, 0, 0);
    if (res != 0)
    {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&prod, NULL, producer, NULL);
    if (res != 0)
    {
        perror("Producer thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&cons, NULL, consumer, NULL);
    if (res != 0)
    {
        perror("Consumer thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("\nWaiting for thread to finish...\n");

    res = pthread_join([prod], NULL);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(cons, NULL);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");

    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}
