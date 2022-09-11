#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//
int perim(double poly1[], double poly2[], int n);
int main()
{
 double x[100]={20, 100, 30, 70};
 double y[100]={40, 90, 10, 60};
 int m=4;
 double pxy;
 double a[100]={90, 10, 40};
 double b[100]={65, 32, 77};
 int n=3;
 double pab;
 pxy=perim(x, y, m);
 pab=perim(a, b, n);
 printf("%lf %lf\n", pxy, pab);
}
int perim(double x[100], double y[100], int size){
	float output, wx, wy, c = {0};
	int i=1;
	while(i<size-1){
		c=0;
		wx=x[i]-x[i-1]; // side 1
		wx*=wx; // side 1 squared
		wy=y[i]-y[i-1]; // side 2
		wy*=wy; // side 2 squared
		c=wx+wy;
		c=sqrtf(c);
		output+=c;
		i++;
	} // still need point[n] vs point [0]
	c=0;
	wx=x[i]-x[0]; // side 1
	wx*=wx; // side 1 squared
	wy=y[i]-y[0]; // side 2
	wy*=wy; // side 2 squared
	c=wx+wy;
	c=sqrtf(c);
	output+=c;
	i++;
	return output;
}