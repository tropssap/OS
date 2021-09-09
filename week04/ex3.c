#include <stdio.h>
#include <stdlib.h>

int main(){
	char string[255];
	while(1){
		printf(">");
		scanf("%s", &string);
		system(string);
	}
return 0;
} 
