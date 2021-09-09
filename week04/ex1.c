#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int n=0;
	int pid=fork();
	if(pid==0){
		printf("Hello from child(%d)",pid-n);}
	else{
		printf("hello from parent(%d)",pid-n);}
	printf("\n");
	return 0;
}
