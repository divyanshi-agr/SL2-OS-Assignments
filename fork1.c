#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define max 5

void merging(int low, int mid, int high, int a[max], int b[max])
{
    int l1, l2, i;

    for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++)
    {
        if (a[l1] <= a[l2])
            b[i] = a[l1++];
        else
            b[i] = a[l2++];
    }

    while (l1 <= mid)
        b[i++] = a[l1++];

    while (l2 <= high)
        b[i++] = a[l2++];

    for (i = low; i <= high; i++)
        a[i] = b[i];
}

void sort(int low, int high, int a[max], int b[max])
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;
        sort(low, mid, a, b);
        sort(mid + 1, high, a, b);
        merging(low, mid, high, a, b);
    }
    else
    {
        return;
    }
}

int main()
{
    pid_t pid;
    int a[5], b[5], i, n;
    char *msg;

    //Accepting input of numbers:
    printf("Enter any 5 numbers:\n");
    for (i = 0; i < 5; i++)
        scanf("%d", &a[i]);

    printf("\n");

    printf("Fork program starting...\n");
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("Fork failed! Process not created.\n");
        exit(1);

    case 0:
        printf("IN CHILD: \n\n");
        printf("The numbers before sorting are:\n");
        for (i = 0; i < max; i++)
            printf("%d\n", a[i]);

        sort(0, max, a, b);
        msg = "BYE CHILD!\n\n";
        n = 2;
        break;

    default:
        printf("IN PARENT: \n\n");
        printf("The numbers before sorting are:\n");
        for (i = 0; i < max; i++)
            printf("%d\n", a[i]);

        sort(0, max, a, b);
        msg = "BYE PARENT!\n\n";
        n = 1;
        break;
    }

    for (; n > 0; n--)
    {
        printf("The sorted array is: \n");
        for (i = 0; i < max; i++)
        {
            printf("%d\n", a[i]);
        }

        puts(msg);
        sleep(1);
    }

    exit(0);
}