#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char*argv[]){

	int fd, fd2, fd3;
	fd = open("source.txt", O_RDONLY);
	int s = lseek(fd, 0 , SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	fd = open("source.txt", O_RDONLY,S_IRWXU);
	fd2 = open("destination1.txt", O_WRONLY, S_IRWXU); 
	fd3 = open("destination2.txt", O_WRONLY, S_IRWXU);

	int loops = s/100; // # of loop
	int remainder = s%100;
	char rem[remainder];
	char buf[100];
	char buf2[50];
	int reads, writes;
	int count = 0;
	int total = s;

	while(total > 0){
		if(count == 0){
			if(total - 100 >= 0){
				read(fd, buf, 100);
				write(fd2, buf, 100);
			}
			else{
				read(fd, rem, total);
				write(fd2, rem, total);
			}
			total -= 100;
			count += 1;
		}
		else{
			if(total - 50 >= 0){
				read(fd, buf2, 50);
				write(fd3, buf2, 50);
			}
			else{
				read(fd, rem, total);
				write(fd3, buf2, 50);
			}
			total -= 50;
			count -= 1;
		}
			
	
	}


	printf("copied successfully");

	close(fd);
	close(fd2);
	close(fd3);

	return 0;
}
