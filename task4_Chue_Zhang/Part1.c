#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
	char n[100];
	do
	{	
		char* arg[100];		   //defining the array ill be passing to execvp		
		int pid1;
		printf("~$ "); 		   //The method im doing requires this to write 
		fgets(n, 100, stdin);      //https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
		char *s = strchr(n, '\n'); //refer to stack overflow for fgets logic
		if(s)			   //refer to stack overflow for fgets logic
			*s = '\0';	   //refer to stack overflow for fgets logic
		arg[0] = strtok(n," ");    //Split the string per space
		int i = 0;		   //Used for increments
		while(arg[i] != NULL)      //This slave works until NULL
		{			   //Remember i++ mean we do then increment
					   //But ++i means increment then assign
			arg[++i] = strtok(NULL, " "); //for putting each element into our arg
		}
		pid1 = fork();		   //fork stuff
		if(pid1 == 0)
		{
			execvp(arg[0], arg);

		}
	}
	while(strcmp(n, "quit") !=0);      // if quit then quit
	wait(NULL);
	return 0;
}
