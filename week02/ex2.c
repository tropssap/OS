#include <stdio.h>
#include <string.h>
int main(void){
printf("Print string for reverse:\n");
char a[1000];
fgets(a, 1000, stdin);
for(int i=strlen(a)-1;i>=0;i--){
printf("%c",a[i]);
}
return 0;
}
