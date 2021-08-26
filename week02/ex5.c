#include <stdio.h>
#include <stdlib.h>

void triangle(int n){
for (int i=0;i<n;i++){
	for (int j=0;j<i;j++)
		printf ("*");
	printf ("\n");
}}

void arrow(int n){
for (int i=0;i<n;i++){
	if ((n/2) >= i)
		for (int j=0;j<=i;j++)
			printf ("*");
	else
		for (int j=0;j<n-i;j++)
			printf ("*");
	printf ("\n");
}}

void rect(int n){
for (int i=0; i<n; i++){
	for (int j=0;j<n;j++)
		printf("*");
	printf("\n");
}}

int main(int argc, char* argv[]){
	triangle(atoi(argv[1]));
	arrow(atoi(argv[1]));
	rect(atoi(argv[1]));
return 0;
}
