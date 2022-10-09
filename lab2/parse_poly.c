#include "FPToolkit.c"
#include "maxpolyfill.c"
#include <math.h>
#include <stdio.h>

// First script: prompts for name of, and opens, 1 .xy file

// # is a symbol for compile-time directives

#define MAXOBJS 10
#define MAXPTS 59000
#define MAXPOLYS 57500

int numpoints;
double x[MAXPTS], y[MAXPTS];
int numpolys;
int psize[MAXPOLYS];
int con[MAXPOLYS][20]; // # polys, poly size
double poly_rgb[MAXPOLYS][3];

void center_and_scale();

int main() {
	FILE *W;

	// Prompt for file name
	char fname[100];
	printf("enter name of .xy file: ");
	scanf("%s", fname);
	W = fopen(fname, "r");

	if (W == NULL) {
		printf("bad file\n");
		exit(0);
	}

	// Get number of coordinates
	fscanf(W, "%d", &numpoints);
	// printf("numpoints = %d\n", numpoints);

	// Get X and Y coordinates
	for (int i = 0; i < numpoints; i++) {
		fscanf(W, "%lf %lf", &x[i], &y[i]);
		// printf("(%3.5lf, %3.5lf)\n", x[i], y[i]);
	}

	// Initialize graphics
	double swidth = 500;
	double sheight = 500;
	screen.x = swidth;
	screen.y = sheight;
	G_init_graphics(screen.x, screen.y);
	G_rgb(0, 0, 0);
	G_clear();

	center_and_scale();

	// Get number of polygons
	fscanf(W, "%d", &numpolys);
	// printf("\nnumpolys = %d\n", numpolys);

	// Get polygon point indices
	for (int i = 0; i < numpolys; i++) {
		fscanf(W, "%d", &psize[i]);
		// printf("\npoly %d: size = %d. \n", i, psize[i]);
		for (int j = 0; j < psize[i]; j++) {
			fscanf(W, "%d", &con[i][j]);
			// printf("point %d ", con[i][j]);
		}
		// printf("\n");
	}

	// Get polygon colors
	for (int i = 0; i < numpolys; i++) {
		fscanf(
			W,
			"%lf %lf %lf",
			&poly_rgb[i][0],
			&poly_rgb[i][1],
			&poly_rgb[i][2]);
		/*
		printf(
			"color %d: %1.3lf %1.3lf %1.3lf\n",
			i,
			poly_rgb[i][0],
			poly_rgb[i][1],
			poly_rgb[i][2]);
		*/
	}

	// Get X,Y values of poly coord indices,
	// and feed to XY_poly_fill()
	for (int i = 0; i < numpolys; i++) {
		double px[20], py[20];
		for (int j = 0; j < psize[i]; j++) {
			px[j] = x[con[i][j]];
			py[j] = y[con[i][j]];
		}
		xy_poly_fill(px, py, psize[i], poly_rgb[i]);
	}

	G_wait_key();
}

void center_and_scale() {
	double biggest[2];
	double smallest[2];

	// Check X and Y coordinates
	biggest[0] = x[0];
	biggest[1] = y[0];
	smallest[0] = biggest[0];
	smallest[1] = biggest[1];
	for (int i = 1; i < numpoints; i++) {
		if (x[i] > biggest[0])
			biggest[0] = x[i];
		if (x[i] < smallest[0])
			smallest[0] = x[i];
		if (y[i] > biggest[1])
			biggest[1] = y[i];
		if (y[i] < smallest[1])
			smallest[1] = y[i];
	}
	printf(
		"\nShape Dimensions: ( %lf, %lf ), ( %lf, %lf )\n",
		smallest[0],
		smallest[1],
		biggest[0],
		biggest[1]);
	double xsize, ysize;
	xsize = biggest[0] - smallest[0];
	ysize = biggest[1] - smallest[1];
	printf("\nShape Size: ( %lf x %lf )\n", xsize, ysize);

	// Overheard Jeff advice: center points at origin, then scale, then move
	// (preserves precision for floats and stuff)

	// Center Shape
	// printf("Centering...\n");
	for (int i = 0; i < numpoints; i++) {
		x[i] -= smallest[0] + xsize / 2;
		y[i] -= smallest[1] + ysize / 2;
	}

	// Scale Shape
	// printf("Scaling...\n");
	double xc, yc, c;

	xc = screen.x / xsize;
	yc = screen.y / ysize;

	if (xc < yc) {
		c = xc;
	} else {
		c = yc;
	}

	printf("Scaling by %lfx...\n\n", c);

	for (int i = 0; i < numpoints; i++) {
		x[i] *= c;
		y[i] *= c;
	}

	for (int i = 0; i < numpoints; i++) {
		x[i] += screen.x / 2;
		y[i] += screen.y / 2;
	}
}