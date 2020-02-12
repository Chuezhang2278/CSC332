//sources
/*
https://www.geeksforgeeks.org/dup-dup2-linux-system-call/ pipe connection using dup2
https://stackoverflow.com/questions/33884291/pipes-dup2-and-exec more dup2 stuff
https://stackoverflow.com/questions/10909011/how-to-use-fork-to-create-only-2-child-processes fork logic
https://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-works-in-linux exec functions
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h> 

int main(){
	pid_t pid1, pid2;
	int mypipe[2]; //pipe
	pipe(mypipe);
	
	pid1 = fork(); //first child created
	if(pid1 == 0){ // working with first child
		close(mypipe[0]); // closing output pipe
		dup2(mypipe[1],1); //working with input pipe
		execlp("ls","ls", "-F" ,NULL);
	}
	else{ // working with second child
		pid2 = fork(); //second child created
		if(pid2 == 0){ 
			close(mypipe[1]); //closing input pipe
			dup2(mypipe[0],0); // working with output pipe
			execlp("nl","nl",NULL);
		}
		else{ //back to parent
			close(mypipe[0]);
			close(mypipe[1]);
			wait(NULL);
			wait(NULL);
		}
			
	}
	return 0;

}



