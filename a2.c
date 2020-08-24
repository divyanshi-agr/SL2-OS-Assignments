#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("I am in a2.c\n");
    printf("PID of a2.c is: %d\n", getpid());
    printf("PID of parent is: %d\n", getppid());

    fork();

    printf("PID of newc is: %d\n", getpid());
    printf("PID of parent of new is: %d\n", getppid());

    return 0;
}