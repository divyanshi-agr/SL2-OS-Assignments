#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

int buffer[N], in = 0, out = 0;
sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    int item;

    while (1)
    {
        // sleep(1);
        printf("Enter no. to insert in buffer: ");
        scanf("%d", &item);

        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        //printf("Produced and inserted element is: %d\n", item);
        in++;

        for (int i = 0; i < N; i++)
        {

            if (buffer[i])
                printf("%d", buffer[i]);
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&full);

        sleep(5);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int x;

    while (1)
    {
        // sleep(7);
        sem_wait(&full);
        sem_wait(&mutex);
        x = buffer[out];
        printf("Consumed element is: %d\n", x);

        buffer[out] = 0;
        out++;

        for (int i = 0; i < N; i++)
        {

            if (buffer[i])
                printf("%d", buffer[i]);
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&empty);
        sleep(5);
    }

    pthread_exit(NULL);
}

int main()
{
    int res;
    pthread_t prod, cons;
    void *thread_result;

    //initializing all 3 semaphores
    res = sem_init(&empty, 0, N);
    if (res != 0)
    {
        perror("Empty semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    res = sem_init(&full, 0, 0);
    if (res != 0)
    {
        perror("Full semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    res = sem_init(&mutex, 0, 1);
    if (res != 0)
    {
        perror("Mutex semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    //creating threads
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

    //joining threads
    res = pthread_join(prod, NULL);
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

    exit(EXIT_SUCCESS);
}
