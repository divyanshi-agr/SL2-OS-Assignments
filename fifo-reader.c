#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
	int file_pipe1[2], file_pipe2[2];
	int count=0, fork_result;
	char* filename = "1.txt";
	char buffer[100];
	char ch[1024];
	FILE *fp;
	pipe(file_pipe2);/* Second pipe created */
	if (pipe(file_pipe1) == 0)/* first pipe created */
		fork_result = fork();    /* Child process created */
	if (fork_result == 0)  
	{
		write(file_pipe1[1], filename, strlen(filename));
		printf("CHILD PROCESS: Wrote filename...\n");
		read(file_pipe2[0], ch, 1024);
		printf("CHILD PROCESS: Its contents are...\n %s", ch);
	}
	else 
	{
		read(file_pipe1[0], buffer, 10);
		printf("PARENT PROCESS: Read filename %s ...\n", buffer);
		fp = fopen(buffer,"r");
		while(!feof(fp)) 
		{
			ch[count] = fgetc(fp);
			count++;
		}
		fclose(fp);
		write(file_pipe2[1], ch, strlen(ch));
		printf("PARENT PROCESS: The Contents are written ...\n");
	}
	return 0;
}