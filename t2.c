// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <pthread.h>

// void *myturn(void *arg)
// {
//     int *iptr = (int *)arg;
//     *iptr = 5;

//     for (int i = 0; i < 7; i++)
//     {
//         sleep(1);
//         printf("My turn and id is %d\n", *iptr);

//         (*iptr)++;
//     }

//     return NULL;
// }

// void *yourturn()
// {
//     {
//         for (int i = 0; i < 4; i++)
//         {
//             sleep(3);
//             printf("Your turn and id is %d\n", i);
//         }
//         return NULL;
//     }
// }

// int main()
// {
//     pthread_t newThread;
//     int *result, v;

//     pthread_create(&newThread, NULL, myturn, NULL);
//     yourturn();

//     pthread_join(newThread, (void *)&result);
//     printf("threads are done and v=%d", v);

//     return NULL;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *myturn(void *arg)
{
    int *iptr;
    iptr = (int *)malloc(sizeof(int));

    *iptr = 5;

    for (int i = 0; i < 5; ++i)
    {
        printf("My id is: %d\n", *iptr);
        (*iptr)++;

        sleep(1);
    }
    pthread_exit(0);
}

void *yourturn(void *arg)
{
    for (int i = 0; i < 3; ++i)
    {
        printf("Your id is: %d\n", i);
        sleep(1);
    }
    pthread_exit(0);
}

int main()
{
    int res;
    pthread_t a_thread;

    // syntax - int pthread_create(pthread_t *thread, pthread_attr_t *attr,
    //						   void *(*start_routine)(void *), void *arg);
    int *v = (int *)malloc(sizeof(int));
    *v = 10;

    res = pthread_create(&a_thread, NULL, myturn, (void *)v);
    if (res != 0)
    {
        perror("\nThread creation failed.");
        exit(EXIT_FAILURE);
    }
    yourturn(NULL);

    res = pthread_join(a_thread, NULL);
    if (res != 0)
    {
        perror("\nThread join failed.");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
