#include "maxlib/FPToolkit.c"

int swidth, sheight;
double CoM[2];

int click_and_save(double *x, double *y) {
	int n;
	double P[2];

	G_rgb(0, 1, 0.5);
	G_fill_rectangle(0, 0, swidth, 20);

	G_rgb(1, 0, 0);
	G_wait_click(P);

	n = 0;
	while (P[1] > 20) {
		x[n] = P[0];
		y[n] = P[1];
		G_circle(x[n], y[n], 2);
		if (n > 0) {
			G_line(x[n - 1], y[n - 1], x[n], y[n]);
		}
		n++;
		G_wait_click(P);
	}

	return n;
}

void get_center(double x[], double y[], int n) {
	double sx = 0, sy = 0;
	for (int i = 0; i < n; i++) {
		sx += x[i];
		sy += y[i];
	}
	CoM[0] = sx / n;
	CoM[1] = sy / n;
}

int in_out(double x[], double y[], int n, double P[2])
// return 1 if point P is inside the convex polygon
// else return 0
{
	for (int i = 0; i < n; i++) {
		int j = i + 1;
		if (i == n - 1) {
			j = 0;
		}

		double dx, dy;
		dx = x[j] - y[i];
		dy = y[j] - y[i];

		// check P
		double r = 0;
		//      AX      +     BY      +            C
		r = (dx * P[1]) - (dy * P[0]) - (dx * y[i] - dy * x[i]);

		printf("%lf\n", r);
	}
}

int main() {
	double xp[1000], yp[1000];
	int n, q;
	double P[2];

	swidth = 300;
	sheight = 300;
	G_init_graphics(swidth, sheight);
	G_rgb(0, 0, 0);
	G_clear();

	G_rgb(1, 0, 0);
	n = click_and_save(xp, yp);
	G_rgb(0, 1, 0);
	G_fill_polygon(xp, yp, n);

	get_center(xp, yp, n) {
	}

	G_wait_click(P);
	in_out(xp, yp, n, P);
	G_rgb(0, 0, 1);
	G_fill_circle(P[0], P[1], 2);

	q = G_wait_key();
}
