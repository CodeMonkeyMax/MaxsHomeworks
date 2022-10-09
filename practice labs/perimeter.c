#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>

struct Vector2 {
	double in[2];
	double x;
	double y;
};

void perimeter_test();
double perimeter(double x[], double y[], int n);

int main(void) {
	printf("Hello World\n");
	perimeter_test();
	return 0;
}

void perimeter_test() {
	double p;
	double u[3] = {100, 300, 400};
	double v[3] = {200, 300, 100};
	p = perimeter(u, v, 3);
	printf("Perimeter: %lf\n", p);
	double a[4] = {500, 700, 600, 400};
	double b[4] = {100, 100, 400, 600};
	p = perimeter(a, b, 4);
	printf("Perimeter: %lf\n", p);
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

	//using 'j' means I don't have to do this stuff:
	//l = 0;
	//difference.x = x[i] - x[0];
	//difference.y = y[i] - y[0];
	//l = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
	//p += l;

	return p;
}