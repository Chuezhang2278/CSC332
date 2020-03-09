#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pid1, pid2;
	
	pid1 = fork();

	if(pid1 < 0){
		printf("error");
		return 1;
	}
	else if(pid1 == 0){
		printf("pid: %d\n", getpid());
		execv("Process_P1", &argv[0]);
	}
	else{
		pid2 = fork();
		sleep(1);

		if(pid2 < 0){
			printf("error");	
			return 1;
		}
		else if(pid2 == 0){
			printf("pid: %d\n", getpid());
			execv("Process_P2", &argv[0]);
		}
		else{
			wait(NULL);
			wait(NULL);
		}
	}
}
