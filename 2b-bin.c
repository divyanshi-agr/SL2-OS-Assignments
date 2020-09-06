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

int main(int argc, char **argv)
{
    int search_no, position, size, i;
    int arr[5];

    printf("I am in a new process now!\n");
    printf("Which number do you want to search from sorted array: ");
    scanf("%d\n", &search_no);

    for (i = 0; i < argc; i++)
    {
        arr[i] = atoi(argv[i]);
    }
    printf("testing...");
    printf("%d", arr[2]);
    //call binary search
    position = binarySearch(arr, 0, i, search_no);

    //print found number's position
    if (position = -1)
    {
        printf("Number not found!\n");
    }
    else
    {
        printf("Number %d found at position %d\n", search_no, position);
    }
}