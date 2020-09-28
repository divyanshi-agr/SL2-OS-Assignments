#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
void *producer(void *arg);
void *consumer(void *arg);

sem_t bin_sem;
sem_t empty;
sem_t full;

int idx=0;
int items[BUFFER_SIZE];

int main() 
{
	int res;
	pthread_t a_thread, b_thread;
	void *thread_result;
	
	for(int i=0;i<BUFFER_SIZE;i++)
		items[i]=-1;
	
	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	res = sem_init(&empty, 0, BUFFER_SIZE);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	res = sem_init(&full, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_create(&a_thread, NULL, producer, &thread_result);
	if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_create(&b_thread, NULL, consumer, &thread_result);
	if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_join(a_thread, NULL);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_join(b_thread, NULL);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	
	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);
}
void *producer(void *arg) 
{
	int item;
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&bin_sem);
		
		//insert into array
		item=rand();
		items[idx]=item;
		idx++;
		
		sem_post(&bin_sem);
		sem_post(&full);
		printf("Produced item is: %d",item);
	}
	pthread_exit(NULL);
}
void *consumer(void *arg) 
{
	int item;
	while(1)
	{
		sem_wait(&full);
		sem_wait(&bin_sem);
		
		//remove from array
		item=items[idx-1];
		items[idx-1]=-1;
		idx--;
		
		sem_post(&bin_sem);
		sem_post(&empty);
		printf("Consumed item is: %d",item);
	}
	pthread_exit(NULL);
}




