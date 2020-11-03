#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define msg_size 50
char *msg = "Hello, I am pipe system call";

int main()
{
    char inbuf[msg_size];
    int p[2], pid, nbytes;

    if (pipe(p) < 0)
        exit(1);

    if ((pid = fork()) > 0)
    {
        write(p[1], msg, msg_size);
        close(p[1]);
        }

    else
    {
        while ((nbytes = read(p[0], inbuf, msg_size)) > 0)
            printf("%s\n", inbuf);
        if (nbytes != 0)
            exit(2);
        printf("Finished reading\n");
    }
    return 0;
}
