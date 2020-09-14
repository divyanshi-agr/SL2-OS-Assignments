#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define num_threads 2

typedef struct thread_data_t
{
    int tid;
    double stuff;
} thread_data_t;

void *thr_func(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;

    printf("hello from thr_func thread id: %d\n", data->tid);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t thr[num_threads];
    int i, rc;

    thread_data_t thr_data[num_threads];

    for (i = 0; i < num_threads; i++)
    {
        thr_data[i].tid = i;
        if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i])))
        {
            fprintf(stderr, "error:pthread_create rc %d\n", rc);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < num_threads; i++)
    {
        pthread_join(thr[i], NULL);
    }

    return EXIT_SUCCESS;
}