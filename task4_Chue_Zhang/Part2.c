#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]) //checks for file existence and readability
{
	char*filepath="quiz_grades.txt";
	int returnval = access (filepath, F_OK);
	int rw = access (filepath, R_OK);
    	if (returnval == 0)
        	printf ("\n %s exists\n", filepath);
    	else
	{
		if (errno == ENOENT)
		{
		printf ("%s does not exist\n", filepath);
		perror("not existing");
		return 1;
		}  
	    	else if (errno == EACCES)
		{
			printf ("%s is not accessible\n", filepath);
			perror("not accessible");
			return 1;
		}
	}
    	if (rw == 0)
        	printf ("\n %s readable\n\n", filepath);
    	else
	{
		printf ("\n %snot readable\n", filepath);
		perror("not readable");
		return 1;
    	}

	FILE *fd = fopen(filepath,"r");
	int rows = 10;
	int columns = 4;
	double scores[columns][rows];

	for(int i = 0; i <= rows-1; i++)
	{
		for(int j = 0; j <= columns-1; j++)
		{
			fscanf(fd,"%lf", &scores[j][i]);
		}
	
	}
	for(int h = 1; h <= rows/2; h++)
	{
		int Parent1 = fork();
			if(Parent1 == 0)
			{
				double temp = 0;
				int Child1 = fork();
				if(Child1 == 0)
				{
					for(int i = 0; i < columns;i++)
					{	
						temp+=scores[i][(h*2)-1];
					}
					printf("Child %d under Manager %d With average: %lf\n\n", (h*2)-1, h, temp/4); 
					exit(0);
				}
				else
				{
					int Child2 = fork();
					temp = 0;
					if(Child2 == 0)
					{	
						for(int i = 0; i < columns;i++)
						{	
							temp+=scores[i][(h*2)];
						}
						printf("Child %d under Manager %d With an Average of: %lf\n", (h*2), h, temp/4);
						exit(0);
					}
					else
					{
						wait(NULL);
						wait(NULL);
				
					}
				}
			}
			else
			{
				wait(NULL);
				exit(0);
			}
		
	}
	fclose(fd);
	return 0;
}
