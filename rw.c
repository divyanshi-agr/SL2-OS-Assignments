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
    printf("Reader %d entered.\n", rc);

    //readers going out of crit section
    sem_wait(&mutex);
    rc--;
    if (rc == 0)
        sem_post(&wrt);

    sem_post(&mutex);
}

void *writer()
{
    sem_wait(&wrt);
    printf("Writer has entered\n");
    sem_post(&y);
    printf("Writer is leaving\n");
}

int main()
{
    int n2, i;
    printf("Enter the number of readers:");
    scanf("%d", &n2);
    printf("\n");
    int n1[n2];
    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);
    for (i = 0; i < n2; i++)
    {
        pthread_create(&writerthreads[i], NULL, reader, NULL);
        pthread_create(&readerthreads[i], NULL, writer, NULL);
    }
    for (i = 0; i < n2; i++)
    {
        pthread_join(writerthreads[i], NULL);
        pthread_join(readerthreads[i], NULL);
    }
}
