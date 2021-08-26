#include <stdio.h>
#include <limits.h>
#include <float.h>
int main(void){
int max = INT_MAX;
float maxf = FLT_MAX;
double maxd = DBL_MAX;
printf("%d - %d \n  %f - %d \n  %f - %d" ,max,sizeof(max),maxf,sizeof(maxf),maxd,sizeof(maxd));
return 0;
}

