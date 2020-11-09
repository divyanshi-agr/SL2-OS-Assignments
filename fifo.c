#include <stdio.h> 
// #include <string.h> 
// #include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
// #include <unistd.h>

int main()
{
    int res = mkfifo("my_fifo1", 0766);
    if (res == 0) 
    printf("FIFO created...\n");
    return(0);
}