#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/times.h>
int main(){
    for(int i=1;i<=10;i++){
        struct rusage rusage;
        char *arr=malloc(1024*1024*100);
        memset(arr,'0',1024*1024*100);
        getrusage(RUSAGE_SELF, &rusage);
        printf("Memmory use:%d\n",rusage.ru_maxrss);
        sleep(1);
    }
}
