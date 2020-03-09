#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
	int pid1;
	char n[100];
	do
	{
		scanf("%s", n);
		pid1 = fork();
		if(pid1 == 0)
		{
			execvp(n, &argv[0]);
		}
		
	}
	while(strcmp(n, "quit") !=0);
	wait(NULL);
	return 0;
}
