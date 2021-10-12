#include <string.h>
#include <unistd.h>
#include "stdlib.h"

int main(){
    for(int i=0;i<10;i++){
        int *a= malloc(1024*1024*800);
        memset(a,'\0',1024*1024*800);
        sleep(1);
    }
    return 0;
}
