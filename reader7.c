#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char read_str[100], write_str[100];
	int fd;

	char *fifo_filename = "fifo0";
	int res = mkfifo(fifo_filename, 0666);

	while (1)
	{
		// read from fifo
		fd = open(fifo_filename, O_RDONLY);
		read(fd, read_str, sizeof(read_str));
		printf("\nOutput: %s", read_str);
		close(fd);

		// write to fifo
		printf("\nInput: ");
		// scanf("%s", write_str);
		gets(write_str);
		fd = open(fifo_filename, O_WRONLY);
		write(fd, write_str, strlen(write_str));
		close(fd);
	}
	
	return 0;
}