#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 10
int *A[SIZE], *B[SIZE];

void *multiplication(void *arg)
{
	int *a, row, col, value, n;
	int *p = (int *)malloc(sizeof(int));
	a = (int *)arg;
	row = a[0];
	col = a[1];
	n = a[2];
	value = 0;
	for (int k = 0; k < n; k++)
		value += A[row][k] * B[k][col];
	*p = value;

	pthread_exit(p);
}

void display_matrix(int *M[SIZE], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d\t", M[i][j]);
		printf("\n");
	}
}

void input_matrix(int *M[SIZE], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%d", &M[i][j]);
	}
}

int main()
{
	int n1, m1, n2, m2, res, args[3], *C[SIZE];
	void *val;

	while (1)
	{
		printf("\nEnter number of rows for A: ");
		scanf("%d", &n1);
		printf("Enter number of cols for A: ");
		scanf("%d", &m1);
		printf("\nEnter number of rows for B: ");
		scanf("%d", &n2);
		printf("Enter number of cols for B: ");
		scanf("%d", &m2);

		if (m1 == n2)
			break;
		printf("\nEnter correct matrices again!\n");
	}
	printf("\nMatrix A elements: \n");
	for (int i = 0; i < n1; i++)
		A[i] = (int *)malloc(m1 * sizeof(int));
	input_matrix(A, n1, m1);
	printf("\nMatrix A : \n");
	display_matrix(A, n1, m1);

	printf("\nMatrix B elements: \n");
	for (int i = 0; i < n2; i++)
		B[i] = (int *)malloc(m2 * sizeof(int));
	input_matrix(B, n2, m2);
	printf("\nMatrix B : \n");
	display_matrix(B, n2, m2);

	for (int i = 0; i < n1; i++)
		C[i] = (int *)malloc(m2 * sizeof(int));

	pthread_t *new_thread[n1];
	for (int i = 0; i < n1; i++)
		new_thread[i] = (pthread_t *)malloc(m2 * sizeof(pthread_t));

	printf("Waiting for threads to finish...\n");

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m2; j++)
		{
			args[0] = i;
			args[1] = j;
			args[2] = m1;
			res = pthread_create(&new_thread[i][j], NULL, multiplication, (void *)args);
			if (res != 0)
			{
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			sleep(1);
		}
	}

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m2; j++)
		{
			res = pthread_join(new_thread[i][j], &val);
			if (res != 0)
			{
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}
			C[i][j] = *((int *)val);
		}
	}
	printf("\nResultant Matrix C : \n");
	display_matrix(C, n1, m2);
	return 0;
}
