#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf ("\n %s exists\n", filepath);
    else{
        if (errno == ENOENT){
        printf ("%s does not exist\n", filepath);
        perror("not existing");
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
    else{
        printf ("\n %s not readable\n", filepath);
        perror("not readable");
        return 1;
    }

    int fd;
    fd = open(filepath, O_RDONLY);
    int s = lseek(fd, 0 , SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char* buffer = malloc(s);
    read(fd,buffer,s);

    int fd2;
    fd2 = open("destination3.txt", O_WRONLY|O_CREAT); //create destination3 if not already created with write only
    if(fd2 == -1){ // error catch 
        printf("error opening desination file");
    }
    else{
        printf("\nSuccesfully copied over\n");
        write(fd2, buffer, s); //copy source.txt over to destination3.txt
    }

    close(fd);
    close(fd2);

    return 0;
    }
