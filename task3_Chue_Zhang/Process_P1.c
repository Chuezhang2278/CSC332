#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
	int fd1, fd2;
	fd1 = open("destination1.txt", O_RDWR|O_CREAT,S_IRWXU);
	fd2 = open("destination2.txt", O_RDWR|O_CREAT,S_IRWXU);
}
