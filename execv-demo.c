#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("I am in execv-demo.c...\n");
    printf("PID of execv-demo.c is: %d\n", getpid());

    char *args[] = {"./hello", NULL};
    execv(args[0], args);

    //Not executed because the process control is in hello.c now and
    //this hello.c process image has replaced the execv-demo process.
    printf("Coming back to execv-demo.c...\n");

    return 0;
}