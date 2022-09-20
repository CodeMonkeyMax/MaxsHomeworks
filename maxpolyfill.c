#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>

struct Vector2 {
	double x;
	double y;
};

struct Polygon {
	int size;
	double x[1000];
	double y[1000];
};

struct Vector2 screen;
struct Vector2 snap_offsets;

void test02();
double check_line(double c1[2], double c2[2], double scany);

void draw_grid() {
	G_rgb(0, 0.2, 0.1);
	for (int i = snap_offsets.x; i < screen.x; i += snap_offsets.x) {
		G_line(0, i, screen.x, i); // x0,y0,x1,y1
		G_line(i, 0, i, screen.y);
	}
}

int click_snap_and_save(double x[], double y[]) {
	draw_grid();
	G_rgb(0.8, 0, 0.4);
	float done_area_y = 20;
	G_fill_rectangle(0, 0, 500, done_area_y);
	int i = 0;
	double in[2];
	G_wait_click(in);
	in[0] =
		floor((in[0] + snap_offsets.x / 2) / snap_offsets.x) * snap_offsets.x;
	in[1] =
		floor((in[1] + snap_offsets.y / 2) / snap_offsets.y) * snap_offsets.y;
	while (in[1] > done_area_y) {
		x[i] = in[0];
		y[i] = in[1];
		G_circle(in[0], in[1], 3);
		G_wait_click(in);

		// The magic numbers
		in[0] = floor((in[0] + snap_offsets.x / 2) / snap_offsets.x) *
			snap_offsets.x;
		in[1] = floor((in[1] + snap_offsets.y / 2) / snap_offsets.y) *
			snap_offsets.y;

		if (in[1] > done_area_y) {
			G_line(in[0], in[1], x[i], y[i]);
		} else {
			G_line(x[i], y[i], x[0], y[0]);
		}
		i++;
	}
	return i;
}

int click_and_save(double x[], double y[]) {
	float done_area_y = 20;
	G_fill_rectangle(0, 0, screen.x, done_area_y);
	int i = 0;
	double in[2];
	G_rgb(0.8, 0, 0.4);
	G_wait_click(in);
	while (in[1] > done_area_y) {
		x[i] = in[0];
		y[i] = in[1];
		G_fill_circle(in[0], in[1], 2);
		G_wait_click(in);
		if (in[1] > done_area_y) {
			G_line(in[0], in[1], x[i], y[i]);
		} else {
			G_line(x[i], y[i], x[0], y[0]);
		}
		i++;
	}
	return i;
}

void sort(double a[], int n) {
	/*
	printf("Array: ");
	for (int i = 0; i < n; i++) {
		printf("%3.0lf ", a[i]);
	}
	printf("\n");
	*/

	// this is a "selection sort"
	double t, r;
	int p;
	// go through array starting at the end
	for (int i = n - 1; i >= 0; i--) {
		r = 0;
		// go through array for largest number
		for (int j = 0; j <= i; j++) {
			if (a[j] > r) {
				p = j;	// store index of largest number
				r = a[j]; // store largest number
			}
		}
		t = a[i];
		a[i] = r;
		a[p] = t;
	}
	/*
	printf("New Array: ");
	for (int i = 0; i < n; i++) {
		printf("%3.0lf ", a[i]);
	}
	printf("\n");
	*/
}

// thought: instead of starting at bottom of screen, start at lowest y val, work
// up to highest y val
int poly_fill(struct Polygon poly, double rgb[3]) {
	G_rgb(rgb[0], rgb[1], rgb[2]);
	// initialize line array
	double lines[1000][2][2];
	// printf("Polygon Size: %i\n", poly.size);
	// store lines
	for (int i = 0; i < poly.size - 1; i++) {
		lines[i][0][0] = poly.x[i];
		lines[i][0][1] = poly.y[i];

		lines[i][1][0] = poly.x[i + 1];
		lines[i][1][1] = poly.y[i + 1];

		// Draw lines to make shape cleaner
		G_line(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
		/*
		printf(
			"Line %i: ( %4.0lf, %4.0lf ) -  ( %4.0lf, %4.0lf )"
			"\n",
			i,
			lines[i][0][0],
			lines[i][0][1],
			lines[i][1][0],
			lines[i][1][1]);
		*/
	}
	lines[poly.size - 1][0][0] = poly.x[poly.size - 1];
	lines[poly.size - 1][0][1] = poly.y[poly.size - 1];
	lines[poly.size - 1][1][0] = poly.x[0];
	lines[poly.size - 1][1][1] = poly.y[0];
	// Draw final Line
	G_line(
		lines[poly.size - 1][0][0],
		lines[poly.size - 1][0][1],
		lines[poly.size - 1][1][0],
		lines[poly.size - 1][1][1]);
	/*
	printf(
		"Line %i: ( %4.0lf, %4.0lf ) -  ( %4.0lf, %4.0lf )"
		"\n",
		poly.size - 1,
		lines[poly.size - 1][0][0],
		lines[poly.size - 1][0][1],
		lines[poly.size - 1][1][0],
		lines[poly.size - 1][1][1]);
	*/

	// start scan line loop
	for (int i = 0; i < screen.y; i++) {
		// if (i % 10 == 0)
		//	G_wait_key();
		double xhit[1000];
		// index of xhit. Resets on every new scan line
		int pint = 0;

		for (int j = 0; j < poly.size; j++) {
			// check_line() called
			// takes start & end points, a reference to an array of intersection
			// points, and current scan line y value
			double test = check_line(lines[j][0], lines[j][1], (double)i);
			if (test != 0) {
				xhit[pint++] = test;
			}
		}

		if (pint >= 2) {
			// printf("i: %4i\n", pint);
			sort(xhit, pint);
			for (int j = 1; j < pint; j++) {
				for (int k = 1; k < pint; k++) {
					double x0 = xhit[k - 1];
					double x1 = xhit[k];
					if (x0 > x1) {
						xhit[k] = x1;
						xhit[k - 1] = x0;
					}
				}
			}

			for (int j = 0; j < pint; j += 2) {
				// printf("draw ( %3.0lf, %3.0lf )\n", xhit[j], xhit[j + 1]);
				G_line(xhit[j], i, xhit[j + 1], i);
			}
		}
	}

	return 0;
}

int xy_poly_fill(double x[], double y[], int size, double rgb[3]) {
	G_rgb(rgb[0], rgb[1], rgb[2]);
	// initialize line array
	double lines[1000][2][2];
	printf("Polygon Size: %i\n", size);
	// store lines
	for (int i = 0; i < size - 1; i++) {
		lines[i][0][0] = x[i];
		lines[i][0][1] = y[i];

		lines[i][1][0] = x[i + 1];
		lines[i][1][1] = y[i + 1];
		/*
		printf(
			"Line %i: ( %4.0lf, %4.0lf ) -  ( %4.0lf, %4.0lf )"
			"\n",
			i,
			lines[i][0][0],
			lines[i][0][1],
			lines[i][1][0],
			lines[i][1][1]);
		*/
	}
	lines[size - 1][0][0] = x[size - 1];
	lines[size - 1][0][1] = y[size - 1];
	lines[size - 1][1][0] = x[0];
	lines[size - 1][1][1] = y[0];
	/*
	printf(
		"Line %i: ( %4.0lf, %4.0lf ) -  ( %4.0lf, %4.0lf )"
		"\n",
		poly.size - 1,
		lines[poly.size - 1][0][0],
		lines[poly.size - 1][0][1],
		lines[poly.size - 1][1][0],
		lines[poly.size - 1][1][1]);
	*/

	// start scan line loop
	for (int i = 0; i < screen.y; i++) {
		// if (i % 10 == 0)
		//	G_wait_key();
		double xhit[1000];
		// index of xhit. Resets on every new scan line
		int pint = 0;

		for (int j = 0; j < size; j++) {
			// check_line() called
			// takes start & end points, a reference to an array of intersection
			// points, and current scan line y value
			double test = check_line(lines[j][0], lines[j][1], (double)i);
			if (test != 0) {
				xhit[pint++] = test;
			}
		}

		if (pint >= 2) {
			// printf("i: %4i\n", pint);
			sort(xhit, pint);
			for (int j = 1; j < pint; j++) {
				for (int k = 1; k < pint; k++) {
					double x0 = xhit[k - 1];
					double x1 = xhit[k];
					if (x0 > x1) {
						xhit[k] = x1;
						xhit[k - 1] = x0;
					}
				}
			}

			for (int j = 0; j < pint; j += 2) {
				// printf("draw ( %3.0lf, %3.0lf )\n", xhit[j], xhit[j + 1]);
				G_line(xhit[j], i, xhit[j + 1], i);
			}
		}
	}

	return 0;
}

double check_line(double c1[2], double c2[2], double scany) {
	struct Vector2 smaller;

	double ybounds[2];

	if (c1[1] > c2[1]) {
		ybounds[0] = c2[1];
		ybounds[1] = c1[1];
	} else {
		ybounds[0] = c1[1];
		ybounds[1] = c2[1];
	}

	if (c1[0] > c2[0]) {
		smaller.x = c2[0];
		smaller.y = c2[1];
	} else {
		smaller.x = c1[0];
		smaller.y = c1[1];
	}

	if (scany >= ybounds[0] && scany < ybounds[1]) {
		double c, ydiff, x;

		c = fabs(c2[0] - c1[0]) / fabs(c2[1] - c1[1]);
		ydiff = fabs(smaller.y - scany);

		x = (ydiff * c) + smaller.x;

		return x;
	}
	return 0;
}

void test02() {
	double xp[500], yp[500], p2;
	int m;
	double P[2];

	snap_offsets.x = 20;
	snap_offsets.y = 20;

	G_rgb(1, 0, 0);
	m = click_snap_and_save(xp, yp);

	struct Polygon poly1;

	for (int i = 0; i < m; i++) {
		poly1.x[i] = xp[i];
		poly1.y[i] = yp[i];
	}
	poly1.size = m;

	double testrgb[3] = {0, 1, 0};

	poly_fill(poly1, testrgb);
	G_wait_key();
}

/*
int main() {
	// Initialize graphics
	double swidth = 500;
	double sheight = 450;
	screen.x = swidth;
	screen.y = sheight;
	G_init_graphics(screen.x, screen.y);
	G_rgb(0, 0, 0);
	G_clear();

	test02();
}
*/