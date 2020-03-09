#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

int main(){
	pid_t pid1, pid2;
	pid1 = fork();
	if(pid1 < 0){
		printf("error");
		return 1;
	}
	else if(pid1 == 0){
		printf("Child one, pID: %d\n", getpid());
		}
	else{
		pid2 = fork();
		if(pid2 < 0 ){
			printf("error");
			return 1;
		}
		else if(pid2 == 0){
			printf("Child two, pID: %d\n", getpid());

		}
		else{
		 wait(NULL);
		 wait(NULL);
		}
			
	}
	
}
