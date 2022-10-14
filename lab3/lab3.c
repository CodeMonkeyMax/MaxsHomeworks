
#include "../maxlib/FPToolkit.c"
#include "../maxlib/M2d_matrix_toolsS.c"
#include "../maxlib/max_poly_tools.c"
#include <math.h>
#include <stdio.h>

// initialize vars here
#define MAXOBJS 10
#define MAXPTS 59000
#define MAXPOLYS 57500

int numpoints[MAXOBJS];			// NOT poly size!
double centerpoint[MAXOBJS][2]; // Definitely keep this, dummy
double x[MAXOBJS][MAXPTS], y[MAXOBJS][MAXPTS];
int numpolys[MAXOBJS];
int numobjs;
int psize[MAXOBJS][MAXPOLYS];
int con[MAXOBJS][MAXPOLYS][20];
double poly_rgb[MAXOBJS][MAXPOLYS][3];

// TODO: I will need to change the format of these variables slightly,
// as they are not quite right for this use case. I think I need to
// get rid of the OBJECTS entirely

// THEN AGAIN, I will probably need to be able to support OBJECTS in
// order to support convex culling windows

// OBJECTIVE: create a poly.
// clicks inside will G_draw a circle of one color,
// clicks outside will G_draw a circle of another color.

int occlude_and_redraw() {
	return 0;
}

int testpoint(double p[2], int pindex) {
	// make lines & test lines? probably don't need to make lines, just test
	// points in for loop with my signature "end-case if statement" for
	// cleanliness
	// double lines[MAXPTS / 2][2][2], ymin, ymax, xmin, xmax;
	int size = psize[0][pindex];
	// for each line in poly: check centerpoint
	int j;
	for (int i = 0; i < size; i++) {
		j = i + 1;
		if (i == size - 1) {
			j = 0;
		}
		double dx = x[0][j] - x[0][i], dy = y[0][j] - y[0][i];
		// dy * Y - dy * X = dx*y0 - dy * x0
	}
}

void findcenterpoint(double out[2], int obji) {
	double s[2] = {0, 0}; // sum
	for (int i = 0; i < psize[obji][obji]; i++) {
		s[0] += x[obji][i];
		s[1] += y[obji][i];
	}
	out[0] = s[0] / psize[obji][obji];
	out[1] = s[1] / psize[obji][obji];
}

int main() {
	double swidth = 450;
	double sheight = 450;
	screen.x = swidth;
	screen.y = sheight;
	G_init_graphics(screen.x, screen.y);
	printf("graphics init success\n");
	G_rgb(0, 0, 0);
	G_clear();

	// double centerpoint[2];
	// draw 1st polygon
	G_rgb(0.8, 0, 0.4);
	psize[0][0] = click_and_save(x[0], y[0]);
	printf("click_and_save 1 success\n");
	findcenterpoint(centerpoint[0], 0);

	G_rgb(0.8, 0, 0.4);
	float done_area_y = 20;
	G_fill_rectangle(0, 0, 500, done_area_y);

	double in[2];
	do {
		printf("click_and_save success\n");
		G_wait_click(in);

		// test in

		G_circle(in[0], in[1], 3);
	} while (in[1] > done_area_y);

	// draw 2nd polygon
	// numpoints[1] = click_snap_and_save(x[1], y[1]);
	// clip 1st polygon by 2nd polygon & redraw
}

int xy_poly_fill(double x[], double y[], int size, double rgb[3]) {
	int ymin = y[0], ymax = y[0];

	G_rgb(rgb[0], rgb[1], rgb[2]);

	// initialize line array
	double lines[1000][2][2];

	// store lines
	for (int i = 0; i < size - 1; i++) {
		if (y[i + 1] < ymin)
			ymin = y[i + 1];
		if (y[i + 1] > ymax)
			ymax = y[i + 1];

		lines[i][0][0] = x[i];
		lines[i][0][1] = y[i];

		lines[i][1][0] = x[i + 1];
		lines[i][1][1] = y[i + 1];
	}
	lines[size - 1][0][0] = x[size - 1];
	lines[size - 1][0][1] = y[size - 1];
	lines[size - 1][1][0] = x[0];
	lines[size - 1][1][1] = y[0];

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
