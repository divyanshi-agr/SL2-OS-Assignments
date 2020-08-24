#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    char *msg;
    int n;

    printf("Fork program starting...\n");
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("Fork failed! Process not created.");
        exit(1);

    case 0:
        msg = "This is the child";
        n = 3;
        break;

    default:
        msg = "This is the parent";
        n = 5;
        break;
    }

    for (; n > 0; n--)
    {
        puts(msg);
        sleep(1);
    }

    exit(0);
}