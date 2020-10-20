#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t mutex;
sem_t wrt;
int rc = 0; //no. of readers

void *reader()
{
    //readers going inside crit section
    sem_wait(&mutex);
    rc++;
    if (rc == 1)
    {
        sem_wait(&wrt);
    }

    sem_post(&mutex);
    printf("Reader %d entered\n", rc);

    //readers going out of crit section
    sem_wait(&mutex);
    printf("Reader %d leaving\n", rc);
    rc--;
    if (rc == 0)
        sem_post(&wrt);

    sem_post(&mutex);
}

void *writer()
{
    sem_wait(&wrt);
    printf("Writer entered\n");
    sem_post(&mutex);
    printf("Writer leaving\n");
}

int main()
{
    int r, i;
    printf("Enter the number of readers:");
    scanf("%d", &r);
    printf("\n");

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < r; i++)
    {
        pthread_create(&reader, NULL, reader, NULL);
        pthread_create(&writer, NULL, writer, NULL);
    }

    for (i = 0; i < r; i++)
    {
        pthread_join(writer, NULL);
        pthread_join(reader, NULL);
    }
}
