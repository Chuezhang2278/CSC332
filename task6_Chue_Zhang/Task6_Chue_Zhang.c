#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t match = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t paper = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tobacco = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t agent = PTHREAD_MUTEX_INITIALIZER;

void *ajent(void *vargp)
{
	int randNum = 0;
	int x = 0;
	do{
		pthread_mutex_lock(&lock);
		randNum = (rand() % (3 + 1 - 1) + 1);
		printf("%d randnum\n",randNum);
		if(randNum == 1)
		{
			printf("Ajent Put tobacco on table\n");
			printf("Ajent Put paper on table\n");
			pthread_mutex_unlock(&match);
		}
		else if(randNum == 2)
		{
			printf("FBI Put tobacco on table\n");
			printf("FBI Put match on table\n");
			pthread_mutex_unlock(&paper);
		}
		else
		{
			printf("Eyy gent Put match on table\n");
			printf("Eyy gent Put paper on table\n");
			pthread_mutex_unlock(&tobacco);
		}
		pthread_mutex_unlock(&lock);
		pthread_mutex_lock(&agent);
		x++;
	}while(x < 5);
}

void *smokey1(void *vargp)
{	
	int x = 0;
	do{
		pthread_mutex_lock(&tobacco);
		pthread_mutex_lock(&lock);
		printf("smokey 1 Pick up match\n");
		printf("smokey 1 Pick up paper\n");
		printf("smokey1 smokes\n");
		sleep(3);
		pthread_mutex_unlock(&agent);
		pthread_mutex_unlock(&lock);
		x++;
	}while(x < 5);
}
void *smokey2(void *vargp)
{	
	int x = 0;
	do{
		pthread_mutex_lock(&match);
		pthread_mutex_lock(&lock);
		printf("smokey2 Pick up paper\n");
		printf("smokey2 Pick up tobacco\n");
		printf("smokey2 smokes\n");
		sleep(3);
		pthread_mutex_unlock(&agent);
		pthread_mutex_unlock(&lock);
		x++;
	}while(x < 5);
}
void *smokey3(void *vargp)
{
	int x = 0;
	do{
		pthread_mutex_lock(&paper);
		pthread_mutex_lock(&lock);
		printf("smonkey3 Pick up tobacco\n");
		printf("smonkey3 Pick up match\n");
		printf("smokey3 smokes\n");
		sleep(3);
		pthread_mutex_unlock(&agent);
		pthread_mutex_unlock(&lock);
		x++;
	}while(x < 5);
}

int main()
{
	pthread_mutex_init(&agent,NULL);
	pthread_mutex_lock(&agent);
	pthread_mutex_init(&paper,NULL);
	pthread_mutex_lock(&paper);
	pthread_mutex_init(&match,NULL);
	pthread_mutex_lock(&match);
	pthread_mutex_init(&tobacco,NULL);
	pthread_mutex_lock(&tobacco);
	pthread_mutex_init(&lock,NULL);
	pthread_mutex_unlock(&lock);

	pthread_t tid[4];
	pthread_create(&tid[0], NULL, &ajent, NULL);
	pthread_create(&tid[1], NULL, &smokey1, NULL);
	pthread_create(&tid[2], NULL, &smokey2, NULL);
	pthread_create(&tid[3], NULL, &smokey3, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}
