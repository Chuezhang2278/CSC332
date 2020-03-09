#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main (int argc, char* argv[])
{
	int fd;
	fd = open("destination3.txt", O_RDONLY|O_CREAT);
	if(-1 == fd){
		printf("\n open() failed with error [%s]\n",strerror(errno));
		return 1;
	}
	else
	{
		printf("\n Open() Successful\n");
	}
	close(fd);
	
	char* filepath = argv[1];
	int returnval;
// Check file existence
	returnval = access (filepath, F_OK);
	if (returnval == 0)
		printf ("\n %s exists\n", filepath);
	else
	{
		if (errno == ENOENT)
			printf ("%s does not exist\n", filepath);
		else if (errno == EACCES){
			printf ("%s is not accessible\n", filepath);
			return 1;
	}

	int rw = access (filepath, R_OK);
	if (rw == 0)
		printf ("\n %s readable\n", filepath);
	else{
		printf ("\n %s not readable\n", filepath);
	}

	int rw2 = access (filepath, W_OK);
	if (rw2 == 0)
		printf ("\n %s writable\n", filepath);
	else{
		printf("\n %s not writable\n", filepath);
		return 1;
	}
	}
}
