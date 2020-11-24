#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char c;
	int opFile, rdFile, wrFile, option;
	char buffer[2048], name[100];
	do
	{
		printf("\n\nEnter your choice\n1. Create file\n2. Write into file\n3. Read file\n0. Exit\n\n");
		scanf(" %d", &option);
		switch(option)
		{
			case 1: 
				printf("Enter the name of the file to create: ");
				scanf("%s", name);
				opFile = open(name, O_CREAT);
				close(opFile);
				break;

			case 2: 
				wrFile = open(name, O_WRONLY);
				printf("Enter the contents to write :\n");
				scanf("%[^\n]s", buffer);                
				write(wrFile, buffer, strlen(buffer));
				close(wrFile);
				break;

			case 3: 
				rdFile = open(name, O_RDONLY);
				read(rdFile, buffer, 2048);
				printf("Contents of the file are:\n%s", buffer);
				close(rdFile);
				break;

			default: 
			case 0: 
				break;
		}
	}while(option);
}