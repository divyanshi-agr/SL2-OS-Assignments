#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>


#define BufferSize 10

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int buffer[BufferSize] = {[0 ... 9]=-1};
int in=0;
int out=0;

void printbuffer()    // display buffer
{		
	printf("Buffer : ");
	for(int i=0;i<10;i++)
	{
		if(buffer[i]!=-1)
			printf("%d ",buffer[i]);
	}
	printf("\n\n");
}

void *producer(void *pno)
{
	while(1)
	{
		int item;
		item = rand()%10;
		sleep(rand()%10);
		sem_wait(&empty);              //decrement empty
		pthread_mutex_lock(&mutex);    // producer thread lock critical section
		buffer[in]=item;
		printf("Producer %d has produced item %d\n",(int *)pno,item);
		printbuffer();
		in = (in+1)%BufferSize;
		pthread_mutex_unlock(&mutex);  // producer thread unlock critical section
		sem_post(&full);               //increment full
	}
		
}

void *consumer(void *cno)
{
	while(1)
	{
		int item;
		sleep(rand()%10);
		sem_wait(&full);             //decrement full
		pthread_mutex_lock(&mutex);  //consumer thread lock critical section
		item = buffer[out];
		buffer[out]=-1;
		printf("Consumer %d has consumed item %d\n",(int *)cno,item);
		printbuffer();
		out = (out+1)%10;
		pthread_mutex_unlock(&mutex);  //consumer thread unlock critical section
		sem_post(&empty);              //increment empty
	}
	
	
}

int main()
{
	int p,c;
	printf("Enter number of producers : ");
	scanf("%d",&p);
	printf("Enter number of consumers : ");
	scanf("%d",&c);
	pthread_t *pro,*con;
	pro=(pthread_t *)malloc(p*sizeof(pthread_t));
	con=(pthread_t *)malloc(c*sizeof(pthread_t));
	pthread_mutex_init(&mutex,NULL);  //initialize mutex
	sem_init(&empty,0,BufferSize);    //initialize empty semaphore
	sem_init(&full,0,0);              //initialize full semaphore
	
	for(int i=0;i<p;i++)
	{
		pthread_create(&pro[i],NULL,(void *)producer, (void *)i); //create producer thread
	}
	for(int i=0;i<c;i++)
	{
		pthread_create(&con[i],NULL,(void*)consumer,(void *)i);  //create consumer thread
	}
	
	
	for(int i=0;i<p;i++)
	{
		pthread_join(pro[i],NULL); //join producer thread
	}
	for(int i=0;i<c;i++)
	{
		pthread_join(con[i],NULL); //join consumer thread
	}
	
	pthread_mutex_destroy(&mutex);    //destroy mutex
	sem_destroy(&empty);		   //destroy empty semaphore
	sem_destroy(&full);		   //destroy full semaphore
	return 0;
}


