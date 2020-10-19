#include <stdio.h>

#define p 5 //no. of processes
#define r 3 //no. of resources

int main()
{
    int alloc[p][r], max[p][r], avail[r], need[p][r], completed[p], safeSequence[p];
    int i, j, process, count = 0;

    for (i = 0; i < p; i++)
        completed[i] = 0;

    // input max matrix
    printf("\n\nEnter the Max Matrix for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    }

    // input allocate matrix
    printf("\n\nEnter the allocation for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    }

    // input availaible array
    printf("\n\nEnter the Available Resources : ");
    for (i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // set the values of remaining need matrix
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // start comparsion of need matrix and availaible matrix
    do
    {
        process = -1;

        for (i = 0; i < p; i++)
        {
            if (completed[i] == 0) //if not completed
            {
                process = i;
                for (j = 0; j < r; j++)
                {
                    if (avail[j] < need[i][j])
                    {
                        process = -1;
                        break;
                    }
                }
            }
            if (process != -1)
                break;
        }

        if (process != -1)
        {
            printf("\nProcess %d is completed!", process);
            safeSequence[count] = process;
            count++;
            for (j = 0; j < r; j++)
            {
                avail[j] += alloc[process][j];
                alloc[process][j] = 0;
                max[process][j] = 0;
                completed[process] = 1;
            }
        }
    } while (count != p && process != -1);

    if (count == p)
    {
        printf("\nThe system is in a safe state!\n");
        printf("Safe Sequence :  ");
        for (i = 0; i < p; i++)
            printf("%d  ", safeSequence[i]);
        printf("\n");
    }
    else
        printf("\nThe system is in an unsafe state!");
}