#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex, wrt;
int buffer = 0, rc = 0;

void *reader(void *arg)
{
    int f;

    while (1)
    {
        f = (int *)arg;
        sem_wait(&mutex);
        rc++;
        if (rc == 1)
            sem_wait(&wrt);

        sem_post(&mutex);
        printf("Reader %d reading data %d\n", f, buffer);

        sem_wait(&mutex);
        rc--;
        if (rc == 0)
            sem_post(&wrt);

        sem_post(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *writer(void *arg)
{
    int f;

    while (1)
    {
        f = (int *)arg;
        sem_wait(&wrt);
        buffer = rand() % 10 + 1;
        printf("Writer %d writing data %d\n", f, buffer);

        sem_post(&wrt);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    int i, r, w;
    pthread_t *read_threads, *write_threads;

    printf("Enter no. of readers: ");
    scanf("%d", &r);

    printf("Enter no. of writers: ");
    scanf("%d", &w);

    read_threads = (pthread_t *)malloc(r * sizeof(pthread_t));
    write_threads = (pthread_t *)malloc(w * sizeof(pthread_t));

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < r; i++)
    {
        pthread_create(&read_threads[i], NULL, reader, (void *)i);
    }

    for (i = 0; i < w; i++)
    {
        pthread_create(&write_threads[i], NULL, writer, (void *)i);
    }

    for (i = 0; i < r; i++)
    {
        pthread_join(read_threads[i], NULL);
    }

    for (i = 0; i < w; i++)
    {
        pthread_join(write_threads[i], NULL);
    }

    return 0;
}