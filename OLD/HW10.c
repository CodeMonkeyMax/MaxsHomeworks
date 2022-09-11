#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int GetPolygonSize(double x[], double y[], double r, int s, bool debug);
int perim(double x[], double y[], int s);
int main()
{
	double r;
	int i, s;
	bool debug = false;
	// # STEP  1 #
	// # # # # # # 
	printf("Enter size of vertex array: ");
	scanf("%d", &s); // get array size
	s--;
	// init array
	double x[s];
	double y[s];
	// fill x array
	i=0;
	while(i<=s){
		printf("Enter x[%d]", i);
		scanf("%lf", &x[i]);
		i++;
	}
	// fill y array
	i=0;
		while(i<=s){
			printf("Enter y[%d]", i);
			scanf("%lf", &y[i]);
			i++;
		}
	if(debug) printf("DEBUG: s=%d\n", s);
	// # STEP  2 #
	// # # # # # # 

	r=GetPolygonSize(x, y, r, s, debug);
	printf("\nAREA: %lf\n", r);

	r=perim(x, y, s);
	printf("PERIMETER: %lf\n", r);
}

int GetPolygonSize(double x[], double y[], double r, int s, bool debug){
	int i=0;
	double fp, sp;
	while(i<s){
		r+=x[i]*y[i+1];
		if(debug) printf("DEBUG: performing x[%d] x y [%d]. Output: %lf. \n",
		 i, i+1, x[i]*y[i+1]);
		i++;
	}
	r+=x[i]*y[0]; // can't forget about the last one!
	if(debug) printf("DEBUG: performing x[%d] x y [%d]. Output: %lf.\n", i, 0, x[i]*y[0]);
	fp=r;
	if(debug) printf("DEBUG: First Product = %lf.\n", fp);
	// # STEP  3 #
	// # # # # # # 
	r=0;
	i=0;
	while(i<s){
		r+=x[i+1]*y[i];
		if(debug) printf("DEBUG: performing x[%d] x y [%d]. Output: %lf.\n", i+1, i, x[i]*y[i+1]);
		i++;
	}
	r+=x[0]*y[i]; // can't forget about the last one!
	if(debug) printf("DEBUG: performing x[%d] x y [%d]. Output: %lf.\n", 0, i, x[0]*y[i]);
	sp=r;
	if(debug) printf("DEBUG: Second Product = %lf.\n", sp);
	// # STEP  4 #
	// # # # # # # 
	r=(fp-sp)/2;
	if(r<0)r*=-1;

	return r;
}

int perim(double x[], double y[], int s){
	double output, wx, wy, c = {0};
	int i=0;
	output = 0;
	//printf("DEBUG: i: %d. s: %d. output: %lf\n", i, s, output);
	while(i<s){
		c=0;
		wx=x[i]-x[i-1]; // side 1
		wx*=wx; // side 1 squared
		wy=y[i]-y[i-1]; // side 2
		wy*=wy; // side 2 squared
		c=wx+wy;
		c=sqrtf(c);
		//printf("DEBUG: Output: %lf. Output += %lf.\n", output, c);
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
	return output;
}