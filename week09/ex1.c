#include "stdint.h"
#include "stdlib.h"
#include "unistd.h"
#include "math.h"
#include "stdio.h"


typedef struct{
    int id;
    uint16_t age;
} page_t;


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please enter number of pages as a programm argument\n");
        return 0;
    }
    int n;
    sscanf(argv[1], "%d", &n);
    FILE* fin = fopen("input.txt", "r");
    page_t *page = malloc(n * sizeof(page_t));
    for(int i = 0; i<n;i++){
    page[i].id = -1;
    }
    int pageID;
    double hit = 0;
    double miss = 0;
    fscanf(fin,"%d", &pageID);
    while(!feof(fin)){
        int hitMoment = 0;
        for(int i=0;i<n;i++){
            page[i].age = page[i].age>>1;

            if(pageID==page[i].id){
                hitMoment++;
                page[i].age = page[i].age | (uint16_t)pow(2,15);

            }
        }
        if(hitMoment != 1){
            miss++;
	    uint16_t min = pow(2,16);
	    int freespace = -1;
	    int swap;
	    for(int i=0;i<n;i++){
	        if(page[i].age<=min && page[i].id !=-1){
	            swap = i;
	            min = page[i].age;
	        }

       		if(page[i].age<=min && page[i].id ==-1){
       		    freespace = i;
        	    min = page[i].age;
        	}

	    }
	    if(freespace!=-1) swap= freespace;
            page[swap].id = pageID;
            page[swap].age = pow(2,15);
        }else{
            hit++;
        }
        fscanf(fin,"%d", &pageID);
    }
    printf("hit:%f, miss:%f, ratio:%f\n", hit,miss,hit/miss);

    fclose(fin);
}
