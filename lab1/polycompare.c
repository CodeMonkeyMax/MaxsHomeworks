#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>

struct Vector2 {
	double in[2];
	double x;
	double y;
};

void done();
double perimeter(double x[], double y[], int n);
double compare(double x[], double y[], int n);
double compareV2(struct Vector2 coords[], int n);
int click_and_save(double x[], double y[]);

int main(void) {
	printf("Hello World\n");
	
	return 0;
}

int click_and_save(double x[], double y[]){
	
}

double compare(double x[], double y[], int n){
	double p1, p2;
	
}

double perimeter(double x[], double y[], int n) {
	int i = 0;
	double p = 0;
	double l;
	struct Vector2 difference;

	while (i < n) {
		int j = (i+1) % n; 
		l = 0;
		difference.x = x[i] - x[j];
		difference.y = y[i] - y[j];
		l = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
		p += l;
		i++;
	}
	return p;
}

void done() {
}