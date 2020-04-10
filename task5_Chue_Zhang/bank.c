#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "sem.h"


#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4, *fd1, *fd2, *fd3;		/* File Pointers */

int sem, count1, count2, count3;

void main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables

	
	if((sem = semget(IPC_PRIVATE,1, 0666 | IPC_CREAT)) == -1)
	{
		printf("Error making sem");
		exit(1);
	}

	sem_create(sem,1);	
	
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);

	//CODE DONE BY ME, WE INIT FOR DAD, SON1 AND SON2 WAIT TIMES. IM DOING THIS SIMILAR TO INIT ABOVE
	fd1 = fopen("dad", "w");
	count1 = 0;
	fprintf(fd1, "%d\n", count1);
	fclose(fd1);
	
	fd2 = fopen("son1", "w");
	count2 = 0;
	fprintf(fd2, "%d\n", count2);
	fclose(fd2);

	fd3 = fopen("son2", "w");
	count3 = 0;
	fprintf(fd3, "%d\n", count3);
	fclose(fd3);


	
	//Create child processes that will do the updates
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{

			P(sem);	
			
			// LITERALLY STEALING PROFESSORS CODE AND JUST REMODELLING IT, REFERRING TO FOPEN, FSCANF, FSEEK
			// WE ARE CHECKING UNFILIAL CHILDREN TOUCHING BANK ACCOUNT	
			fd2 = fopen("son1", "r+"); // r+ MEANS READ AND WRITE ACCESS
			fscanf(fd2, "%d", &count2);
			fseek(fd2, 0L, 0);
			count2++;	     // INCREMENTING COUNT PER INSTRUCTIONS IN STEP 2 TO COUNT PROCESSES 	
			fprintf(fd2, "%d\n", count2);
			fclose(fd2);

			fd3 = fopen("son2", "r+"); 
			fscanf(fd3, "%d", &count3);
			fseek(fd3, 0L, 0);
			count3++;
			fprintf(fd3, "%d\n", count3);

			fclose(fd3);	
			// WE ARE CHECKING UNFILIAL CHILDREN TOUCHING BANK ACCOUNT				

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);		
	
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */

			V(sem);
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
				P(sem);
				
				//WE ARE NOW WORKING WITH UNFILIAL CHILD 2 AND DAD SINCE UNFILIAL CHILD 1 IS DOING HIS PROCESS
				fd1 = fopen("dad", "r+");
				fscanf(fd1, "%d", &count1);
				fseek(fd1, 0L , 0);
				count1++;
				fprintf(fd1, "%d\n", count1);
				fclose(fd1);

				fd3 = fopen("son2", "r+");
				fscanf(fd3, "%d", &count3);
				fseek(fd3, 0L, 0);
				count3++;
				fprintf(fd3, "%d\n", count3);
				fclose(fd3);
				//WE ARE NOW WORKING WITH UNFILIAL CHILD 2 AND DAD SINCE UNFILIAL CHILD 1 IS DOING HIS PROCESS

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				V(sem);
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					P(sem);

					//WE ARE NOW WORKING WITH UNFILIAL CHILD 1 AND DAD SINCE UNFILIAL CHILD 2 IS DOING HIS PROCESS

					fd1 = fopen("dad", "r+");
					fscanf(fd1, "%d", &count1);
					fseek(fd1, 0L, 0);
					count1++;
					fprintf(fd1, "%d\n", count1);
					fclose(fd1);

					fd2 = fopen("son1", "r+");
					fscanf(fd2, "%d", &count2);
					fseek(fd2, 0L, 0);
					count2++;
					fprintf(fd2, "%d\n", count2);
					fclose(fd2);

					//WE ARE NOW WORKING WITH UNFILIAL CHILD 1 AND DAD SINCE UNFILIAL CHILD 2 IS DOING HIS PROCESS

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					V(sem);	
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}




