//Sources
//https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
//https://www.geeksforgeeks.org/multithreading-c-2/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g = 0; //
int h = 0; // For counting the chickens crossing the road
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // need to init it or program yells at you

void *NorthHomies(void *vargp) //North homies
{	
	pthread_mutex_lock(&lock); // Lock this 
	g++;
	printf("North dude #%d can cross the bridge\n", g);
	printf("North dude #%d crossing bridge\n", g);
	sleep(3);
	printf("North dude #%d has left the bridge\n", g);
	printf("\n");
	pthread_mutex_unlock(&lock); // Only when this is done will you proceed
}

void *SouthHomies(void *vargp) // Proceeding to south homies
{
	pthread_mutex_lock(&lock); // Lock the south homies action
	h++;
	printf("South dude #%d can cross the bridge\n", h);
	printf("South dude #%d crossing bridge\n", h);
	sleep(3);
	printf("South dude #%d has left the bridge\n", h);
	printf("\n");
	pthread_mutex_unlock(&lock); // Only proceed when done
}

int main()
{
	int i;
	pthread_t tid[2]; // We got two pthreads for North abd south homies

	for(i = 0;i < 5;i++)
	{
		pthread_create(&tid[0], NULL, &NorthHomies, NULL); // method for making pthreads 
		pthread_create(&tid[1], NULL, &SouthHomies, NULL);
	}	
	pthread_join(tid[0], NULL); // kill process
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock); // kill lock
	return 0;
}
