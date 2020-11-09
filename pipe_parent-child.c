#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd1[2]; // Used to store two ends of first pipe
    int fd2[2]; // Used to store two ends of second pipe

    char fixed_str[] = " System";
    char input_str[50];
    pid_t p;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    printf("Enter a string:");
    scanf("%s", input_str);
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    //parent process
    else if (p > 0)
    {
        char pal_str[100];

        close(fd1[0]); // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0], pal_str, 100);
        printf("Concatenated string is: %s\n", pal_str);
        close(fd2[0]);
    }

    // child process
    else
    {
        close(fd1[1]); // Close writing end of first pipe

        // Read a string using first pipe
        char pal_str[100];
        read(fd1[0], pal_str, 100);

        // Concatenate a fixed string with it
        // int k = strlen(pal_str);
        int i;
        for (i = 0; i < strlen(input_str); i++)
          {
            pal_str[i] = input_str[strlen(input_str)-i-1];
          }  

        pal_str[k] = '\0'; // string ends with '\0'

        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], pal_str, strlen(pal_str) + 1);
        close(fd2[1]);

        exit(0);
    }
}