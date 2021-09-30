#include <string.h>
#include "stdlib.h"
#include "stdio.h"


void *reAllocation(void *ptr, size_t size) //size_t in bytes
{

    if(size>0) {   
        void *newptr;
        newptr = malloc(size);
        if (ptr != NULL){
            newptr = memcpy(newptr, ptr, size);
            free(ptr);
        }
        return newptr;
    }
    else
        free(ptr);
    return NULL;
}

int main(){
    int n=5;
    int *a1= malloc(n*sizeof (int));
    for(int i=0;i<n;i++){
        a1[i]=i;
        printf("%d ",a1[i]);
    }
    int n2=7;
    a1=reAllocation(a1,n2*sizeof(int));
    printf("\n");
    for(int i=0;i<n2;i++){
        if(i>=n)
            a1[i]=0;
        printf("%d ",a1[i]);
    }
    return 0;
}
