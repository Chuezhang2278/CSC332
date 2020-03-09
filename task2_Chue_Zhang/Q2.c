#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

int main(){

	int a=10, b=25, fq=0, fr=0;
	fq=fork(); // fork a child - call it Process Q
	if(fq==0){
		a=a+b; 
		printf("A value of Q: %d\n", a);
		printf("B value of Q: %d\n", b);
		printf("pID value of Q: %d\n", getpid());
		fr=fork(); // fork another child - call it Process R
		if(fr!=0){
			b=b+20;
			printf("A value of R: %d\n", a);
			printf("B value of R: %d\n", b);
			printf("pID value of R: %d\n", getpid());
		}
		else{
			a=(a*b)+30;
			printf("A value of R: %d\n", a);
			printf("B value of R: %d\n", b);
			printf("pID value of R: %d\n", getpid());
		}
	}
	else{
		b=a+b-5;
			printf("A value of Q: %d\n", a);
			printf("B value of Q: %d\n", b);
			printf("pID value of Q: %d\n", getpid());
	}
	wait(NULL);
	wait(NULL);
}
