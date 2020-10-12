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
