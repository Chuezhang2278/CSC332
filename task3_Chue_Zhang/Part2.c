#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pid1;
	
	pid1 = fork();

	if(pid1 < 0){
		printf("error");
		return 1;
	}
	else if(pid1 == 0){
		execvp("ls", &argv[0]);
		printf("pid: %d\n", getpid());
	}
	else{
		printf("Parent\n");
		wait(NULL);
	}
}
