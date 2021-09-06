#include <stdio.h>

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  

void bubbleSort(int arr[],int n) 
{ 
    int i, j; 
    for (i = 0; i < n; i++)  
    for (j = 0; j < n-i; j++) 
        if (arr[j] > arr[j+1]) 
            swap(&arr[j], &arr[j+1]); 
} 
  
int main(){
int array[10]={1,5,8,2,9,3,0,4,7,6};
bubbleSort(array,10);
for(int i=0;i<10;i++){
	printf("%d ",array[i]);
}
return 0;
}
