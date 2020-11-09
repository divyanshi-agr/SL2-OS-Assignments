#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
	int fd,fd1;
	char * myfifo1 = "fifo1";
	char * myfifo2 = "fifo2";
	char buf[512];
	mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0777);
	fd = open(myfifo1, O_WRONLY);
	write(fd, "Hello friends.. \nWelcome..\nI am Divyanshi", 55);
	printf("Data wrote in Fifo1 by writer\n");
	close(fd);
	fd1 = open(myfifo2, O_RDONLY);
	read(fd1, buf, sizeof(buf));
	printf("Data received by Fifo2 by writer\n");
	printf("%s",buf);
	close(fd1);
	return 0;
}