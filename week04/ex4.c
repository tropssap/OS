#include <stdio.h>
#include <stdlib.h>

int main(){
        char string[255];
	char eol;
        while(1){
		printf(">");
                scanf("%255[^\n]%c", &string,&eol);
                system(string);
        }
return 0;
}

