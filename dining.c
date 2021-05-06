#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>


sem_t *cs;
pthread_mutex_t mutex;
enum st{THINKING, EATING, HUNGRY};
enum st *state;
pthread_cond_t *condition;

int N;

void* philospher(void*);
void grab_fork(int);
void put_fork(int);
void test(int);
void think(int);
void eat(int);

int main()
{
	pthread_t *phil;
	int i,err;
	int *index;
	
	printf("\nEnter no. of philosphers\n");
	scanf("%d",&N);
	
	
	pthread_mutex_init(&mutex, NULL);
	
	
	phil = (pthread_t*) malloc(N * sizeof(pthread_t));
	index = (int*) malloc(N * sizeof(int));
	cs = (sem_t*) malloc(N * sizeof(sem_t));
	state = (enum st*) malloc(N * sizeof(enum st));
	condition =(pthread_cond_t*)malloc(N * sizeof(pthread_cond_t));
	
	
	for(i=0;i<N;i++)
	{
		state[i] = THINKING;
		sem_init(&cs[i],0,0);		//binary sem are initialised by 0
		pthread_cond_init(&condition[i],NULL);
	}
	
	
	for(i=0;i<N;i++)
	{
		index[i]=i;
		err = pthread_create(&phil[i],NULL,philospher,(void*)&index[i]);
		if(err!=0)
		{
			printf("\nError in thread creation!!!");
			exit(0);
		}
	}
	
	
	for(i=0;i<N;i++){
		err = pthread_join(phil[i],NULL);
		if(err!=0)
		{
			printf("\nError in thread joining!!!");
			exit(0);
		}
	}

return 0;
}

void *philospher(void *arg)
{
	int i = *(int*)arg;
	while(1)
	{
		printf("\nPhilospher[%d] is thinking\n",i);
		sleep(3);
		grab_fork(i);
		put_fork(i);
	}
}

void grab_fork(int num)
{
	pthread_mutex_lock(&mutex);
	printf("\nPhilospher[%d] is hungry\n",num);
	state[num] = HUNGRY;
	pthread_mutex_unlock(&mutex);
	test(num);
	pthread_mutex_lock(&mutex);
	if (state[num] != EATING)
	{
		pthread_cond_wait(&condition[num],&mutex);
	}
	pthread_mutex_unlock(&mutex);
}

void put_fork(int num)
{
	pthread_mutex_lock(&mutex);
	state[num] = THINKING;
	test(num);
	test((num+1)%N);
	pthread_mutex_unlock(&mutex);
}

void test(int i)
{
	if(state[i%N]==HUNGRY && state[(i+N-1)%N] != EATING && state[(i+1)%N] != EATING)
	{
		printf("\nPhilospher[%d] is eating\n",i);
		sleep(rand()%4);
		state[i] = EATING;
		pthread_cond_signal((condition+i));
	}
}



