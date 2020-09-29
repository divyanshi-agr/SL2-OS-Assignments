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
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int item;

    while (1)
    {
        sleep(1);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        item = rand() % 10;
        buffer[in] = item;
        in = (in + 1) % N;
        printf("Producer %d produced element: %d\n", (int *)arg, item);
        for (int i = 0; i < N; i++)
        {
            if (buffer[i])
                printf("%d\t", buffer[i]);
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int x;

    while (1)
    {
        sleep(5);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        x = buffer[out];

        buffer[out] = 0;
        out = (out + 1) % N;
        printf("\nConsumer %d consumed element: %d\n\n", (int *)arg, x);
        for (int i = 0; i < N; i++)
        {
            if (buffer[i])
                printf("%d\t", buffer[i]);
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    pthread_exit(NULL);
}

int main()
{
    int res, pr, co, i, arg;
    pthread_t *prod, *cons;
    void *thread_result;

    printf("Enter no. of producers: ");
    scanf("%d", &pr);
    printf("Enter no. of consumers: ");
    scanf("%d", &co);

    printf("\n");

    prod = (pthread_t *)malloc(pr * sizeof(pthread_t));
    cons = (pthread_t *)malloc(co * sizeof(pthread_t));

    //initializing 2 semaphores and 1 mutex
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

    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0)
    {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    //creating multiple threads
    for (i = 0; i < pr; i++)
    {
        res = pthread_create(&prod[i], NULL, producer, (void *)i);
        if (res != 0)
        {
            perror("Producer thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < co; i++)
    {
        res = pthread_create(&cons[i], NULL, consumer, (void *)i);
        if (res != 0)
        {
            perror("Consumer thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("\nWaiting for thread to finish...\n");

    //joining threads
    for (i = 0; i < pr; i++)
    {
        res = pthread_join(prod[i], NULL);
        if (res != 0)
        {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < co; i++)
    {
        res = pthread_join(cons[i], NULL);
        if (res != 0)
        {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("Thread joined\n");

    exit(EXIT_SUCCESS);
}
