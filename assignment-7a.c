#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>

int main() 
{
	int fd1[2];
	int fd2[2];
	const int BSIZE = 100;
	char buf[BSIZE];
	ssize_t nbytes;
	int status1, status2;
	char input_str[100]; 
	char file_contents[1000];
	char filename[100];
	FILE *fptr;
	
	status1 = pipe(fd1);
	status2 = pipe(fd2);

	if (status1 == -1 || status2 == -1 ) {
		printf("Execution failed\n");
	}
	switch (fork()) 
	{
		case -1:
			break;
		case 0: 
			close(fd1[1]); 
			char filename_c[100];
			read(fd1[0], filename_c, 100); 
			fptr = fopen(filename_c, "r");
			if (fptr == NULL) 
		    	{ 
				printf("Cannot open file \n"); 
				exit(0); 
		    	} 
		    	fread(file_contents, sizeof(file_contents)+1, 1, fptr);
		    	fclose(fptr);
			close(fd1[0]); 
			
			close(fd2[0]); 
			write(fd2[1], file_contents, strlen(file_contents) + 1);
			close(fd2[1]);
			exit(EXIT_SUCCESS);
		default: 
			printf("Enter name of the file to be read: ");
			scanf("%s", filename);
			close(fd1[0]); 
			write(fd1[1], filename , strlen(filename) + 1); 
			close(fd1[1]); 
			
			wait(NULL);
			
			close(fd2[1]);
			read(fd2[0], file_contents, sizeof(file_contents)+ 1);
			printf("The contents of the file are : \n\n%s\n", file_contents); 
        		close(fd2[0]); 
        }
	exit(EXIT_SUCCESS);
}