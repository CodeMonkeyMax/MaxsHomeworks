#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
	double x, m, o, p[1000]; //input, mean, output, and "p" for some reason
	int i, xi, s; // index and TRUE array size
	scanf("%lf", &x);
	while (x >= 0){ // Take inputs
		//printf("x = %lf\n", x);
		p[i] = x;
		i++;
		scanf("%lf", &x);
	}
	s = i;
	//printf("Array Size: %i\n", s); //Store Array Size

	i=0;
	x=0;
	while (i<s){ // Calculate mean
		x+=p[i];
		//printf("running for index %i. p= %lf...\n", i, p[i]);
		i++;
	}
	o=x/s;
	printf("\nMean: %lf\n", o);
	m=o;

	x=0;
	i=0;
	xi=0;
	while(i<s){ // Calculate Variances
		p[i] = p[i]-m;
		printf("Difference at p[%i]: %lf\n", i, p[i]);
		p[i]*=p[i];
		x+=p[i];
		i++;
		xi++;
		//printf("xi: %i", xi);
	}
	x/=xi;
	o=sqrtf(x);
	printf("o = %lf\n", o);
}