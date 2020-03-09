#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char*argv[]){
	char* filepath = argv[1];
	int returnval;
	returnval = access (filepath, F_OK);
	if (returnval == 0)
		printf ("\n %s exists\n", filepath);
	else{
	if (errno == ENOENT){
		printf ("%s does not exist\n", filepath);
		perror("not existing" );
		return 1;
		}
	else if (errno == EACCES){
		printf ("%s is not accessible\n", filepath);
		perror("not accessible");
		return 1;
		}
	}

	int rw = access (filepath, R_OK);
	if (rw == 0)
		printf ("\n %s readable\n", filepath);
	else
	{
		printf ("\n %s not readable\n", filepath);
		perror("not readable");
		return 1;
	}

	int fd, fd2;
	fd = open(filepath, O_RDONLY);
	int s = lseek(fd, 0 , SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char* buffer = malloc(s);

	fd2 = open("destination3.txt", O_WRONLY|O_CREAT); // create dest3 if not made, write only
	char* buffer2 = "XYZ"; // add XYZ    

	int loops = s/100; // # of loop
	int remainder = s%100; // find remainding after loop calc
	char buf[100];
	int reads, writes;


	for (int i=0 ; i < loops ; i++) 
		{
			reads = read(fd, buf, 100);
			for (int j=0 ; j < 100 ; j++)
			{
				if (buf[j] == '1') buf[j]='A'; // 1 = A
			}
			writes =  write (fd2,buf,100); // write to destination3.txt
			writes =  write (fd2,buffer2,3); // xyz
		}

	char Buf[remainder]; 
	read(fd, Buf, remainder);	

	for (int u=0 ; u < remainder ; u++)  // remaining below 100
		{
			if (Buf[u] == '1') Buf[u]='A';  
			if (u == remainder-1)           
			{
				write (fd2,Buf,remainder);  //reamining copy over
				write (fd2,buffer2,3); //xyz
			}

		}
	printf("copied successfully");

	close(fd);
	close(fd2);

	return 0;
}
