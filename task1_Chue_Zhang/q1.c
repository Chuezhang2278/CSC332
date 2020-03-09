#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

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
        perror("not existing:");
        return 1;
    }
    else if (errno == EACCES){
        printf ("%s is not accessible\n", filepath);
        perror("not accessible:");
        return 1;
    }
}

    int rw = access (filepath, R_OK);
    if (rw == 0)
        printf ("\n %s readable\n", filepath);
    else{
        printf ("\n %s not readable\n", filepath);
        perror("not readable:");
    }

    int fd; //initializing fd
    fd = open(filepath, O_RDONLY); //read only filepath
    int s = lseek(fd, 0 , SEEK_END); //find end of file
    lseek(fd, 0, SEEK_SET); //find start
    char* buffer = malloc(s); //allocating bytes
    int r = read(fd,buffer,s); // reading 

    for(int i=0;i<=s;i++)
    {
        printf("%c",buffer[i]); //print content
    }
    close(fd); //finished, close
    return 0;
}
