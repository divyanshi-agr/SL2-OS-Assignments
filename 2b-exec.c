#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

#define max 5

//Quick sort algorithm
void quick_sort(int a[max], int first, int last)
{
    int i, j, pivot, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (a[i] <= a[pivot] && i < last)
                i++;
            while (a[j] > a[pivot])
                j--;
            if (i < j)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        temp = a[pivot];
        a[pivot] = a[j];
        a[j] = temp;
        quick_sort(a, first, j - 1);
        quick_sort(a, j + 1, last);
    }
}

int main()
{
    pid_t pid;
    int a[5], b[5], i, temp, j;
    int option;
    char buffer_str[10];
    char *child_name = "./b";
    char *args[20];

    //Accepting input of unsorted numbers:
    printf("Enter any 5 numbers:\n");
    for (i = 0; i < 5; i++)
        scanf("%d", &a[i]);

    printf("\n");

    //Printing unsorted array
    printf("The numbers before sorting are:\n");
    for (i = 0; i < max; i++)
        printf("%d\n", a[i]);

    //Sorting in Parent using Quick Sort
    quick_sort(a, 0, max - 1);

    //Printing the sorted numbers
    printf("The sorted array is: \n");
    for (i = 0; i < max; i++)
    {
        printf("%d\n", a[i]);
    }
    printf("\n");

    printf("Fork program starting...\n\n");
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        printf("IN CHILD:");

        //Recieved sorted array
        //call exec to search using binary program

        printf("Child's PID is : %d", getpid());
        printf("Child's Parent ID is : %d", getppid());

        args[0] = child_name;
        for (i = 0; i < max; i++)
        {
            sprintf(buffer_str, "%d", a[i]);
            args[i + 1] = malloc(strlen(buffer_str));
            strcpy(args[i + 1], buffer_str);
        }

        args[max + 1] = NULL;
        execv(args[0], args);

        break;

    default:

        wait(NULL);

        printf("\nBACK IN PARENT:\n");
        printf("Parent's PID is : %d\n", getpid());
        break;
    }
}