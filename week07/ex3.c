#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){
    srand(time(NULL));

    printf("Enter original array size:");
    int n1=0;
    scanf("%d",&n1);

    int* a1 = malloc(n1*sizeof (int));
    int i;
    for(i=0; i<n1; i++){
        a1[i]=100;


        printf("%d ",a1[i] );
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2=0;
    scanf("%d",&n2);

    //Dynamically change the array to size n2
    a1 = realloc(a1,n2*sizeof (int));

    //If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.
    for(i=0;i<n2;i++){
        if(i<n1)
            continue;
        a1[i]=0;
    }
    /*
    Fill
    In
    */


    for(i=0; i<n2;i++){
        //Print each element out (to make sure things look right)
        printf("%d ",a1[i]);
    }
    printf("\n");

    //Done with array now, done with program :D

    return 0;
}

