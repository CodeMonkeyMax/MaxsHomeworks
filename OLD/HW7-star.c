#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
int main(){
	int n, li, pi, i, m; //n, line index, plus index, index, midpoint
	//enter n
	n=0;
	printf("Enter n: ");
	scanf("%d", &n);
	i=1;
	m=0;
	//calculate midpoint
	m = 2*n-1;
	//printf("Debug: m = %d", m);
	//begin printing from top
	while(i<=n){
		//spaces to midpoint
		li=0;
		while(li<1+(m-i)-n){ // at i=n, should print 0 spaces
			printf(" ");
			li++;
		}
		//+'s 
		pi=0;
		//printf("\nDebug: (2*i)+1): %d", (2*i)+1);
		while(pi<(2*i)-1){
			printf("+");
			pi++;
		}
		//return
		i++;
		printf("\n");
	}
	i-=2;
	while(i>=0){
		//spaces to midpoint
		li=0;
		while(li<1+(m-i)-n){ // at i=n, should print 0 spaces
			printf(" ");
			li++;
		}
		//+'s 
		pi=0;
		//printf("\nDebug: (2*i)+1): %d", (2*i)+1);
		while(pi<(2*i)-1){
			printf("+");
			pi++;
		}
		//return
		i--;
		printf("\n");
	}
}