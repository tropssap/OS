#include <stdio.h>

void swap(int* x, int* y){
int temp=*x;
*x=*y;
*y=temp;
}

int main(void){
int x,y;
printf("Print two integers:");
scanf("%d %d",&x, &y);
swap(&x,&y);
printf("%d %d",x,y);
return 0;
}
