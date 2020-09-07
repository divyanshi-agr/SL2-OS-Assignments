#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int search_no, position, size, i;
    int arr[10];

    for (i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    int n = sizeof(arr);
    printf("I am in a new process within child!\n\n");
    printf("Which number do you want to search from sorted array: ");
    scanf("%d", &search_no);

    //call binary search
    position = binarySearch(arr, 0, n - 1, search_no);

    //print found number's position
    if (position == -1)
    {
        printf("Number not found!\n");
    }
    else
    {
        printf("Number %d found at position %d\n", search_no, position);
    }
}