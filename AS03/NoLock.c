//Sources
//https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
//https://www.geeksforgeeks.org/multithreading-c-2/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g = 0;
int h = 0;
void *NorthHomies(void *varg) // North homies function to be threaded
{
	g++; //increment so we know which dude we on
	printf("North dude #%d can cross the bridge\n", g);
	printf("North dude #%d crossing bridge\n\n", g);
	sleep(3);
	printf("North dude #%d has left the bridge\n", g);
	printf("\n");
}

void *SouthHomies(void *vargp) // South homieson the move
{
	h++; // we increment the dude
	printf("South dude #%d can cross the bridge\n", h);
	printf("South dude #%d crossing bridge\n\n", h);
	sleep(3);
	printf("South dude #%d has left the bridge\n", h);
	printf("\n");
}

int main()
{
	int i;
	pthread_t tid[2]; //two pthreads

	for(int i; i < 5;i++)
	{	
		pthread_create(&tid[0], NULL, &NorthHomies, NULL); // creating pthread
		pthread_create(&tid[1], NULL, &SouthHomies, NULL); // creating p thread
	}	
	pthread_join(tid[0], NULL); //kill pthread
	pthread_join(tid[1], NULL); //kill pthread
	return 0;
}
