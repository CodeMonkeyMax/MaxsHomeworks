#include "FPToolkit.c"
#include "maxpolyfill.c"
#include <math.h>
#include <stdio.h>

// Multi Draw 1: prompts for name of, and draws, up to 10 .xy objects

// FIXME: sometimes multi_draw gets sad and disfigures my first object
// No longer first object.

// # is a symbol for compile-time directives
#define MAXOBJS 10
#define MAXPTS 59000
#define MAXPOLYS 57500

int numpoints;
double x[MAXOBJS][MAXPTS], y[MAXOBJS][MAXPTS];
int numpolys;
int numobjs;
int psize[MAXOBJS][MAXPOLYS];
int con[MAXOBJS][MAXPOLYS][20];
double poly_rgb[MAXOBJS][MAXPOLYS][3];

void read_object(FILE *f, int obji);
void draw_object(int obji);
void center_and_scale(int obji);

int main() {
	// Prompt for num objects
	printf("how many objects? ");
	scanf("%d", &numobjs);

	// Initialize graphics
	double swidth = 450;
	double sheight = 450;
	screen.x = swidth;
	screen.y = sheight;
	G_init_graphics(screen.x, screen.y);

	for (int i = 0; i < numobjs; i++) {
		FILE *W;
		// Prompt for file names
		char fname[100];
		printf("enter name of .xy file #%d: ", i);
		scanf("%s", fname);
		W = fopen(fname, "r");
		read_object(W, i);
		center_and_scale(i);
	}

	/*
	for (int i = 0; i < numobjs; i++) {
		center_and_scale(i);
		draw_object(i);
		G_wait_key();
	}
	*/

	int k;
	do {
		k = G_wait_key();
		printf("%d\n", k);
		G_rgb(0, 0, 0);
		G_clear();
		if (k >= 48 && k <= 58) {
			draw_object(k - 48);
		}
	} while (k != 'q');
	exit(0);
}

void read_object(FILE *f, int obji) {
	if (f == NULL) {
		printf("bad file\n");
		exit(0);
	}

	// Get number of coordinates
	fscanf(f, "%d", &numpoints);
	// printf("numpoints = %d\n", numpoints);

	// Get X and Y coordinates
	for (int i = 0; i < numpoints; i++) {
		fscanf(f, "%lf %lf", &x[obji][i], &y[obji][i]);
		// printf("(%3.5lf, %3.5lf)\n", x[i], y[i]);
	}

	// Get number of polygons
	fscanf(f, "%d", &numpolys);
	// printf("\nnumpolys = %d\n", numpolys);

	// Get polygon point indices
	for (int i = 0; i < numpolys; i++) {
		fscanf(f, "%d", &psize[obji][i]);
		// printf("\npoly %d: size = %d. \n", i, psize[i]);
		for (int j = 0; j < psize[obji][i]; j++) {
			fscanf(f, "%d", &con[obji][i][j]);
			// printf("point %d ", con[i][j]);
		}
		// printf("\n");
	}

	// Get polygon colors
	for (int i = 0; i < numpolys; i++) {
		fscanf(
			f,
			"%lf %lf %lf",
			&poly_rgb[obji][i][0],
			&poly_rgb[obji][i][1],
			&poly_rgb[obji][i][2]);
	}
}

void draw_object(int obji) {
	// Get X,Y values of poly coord indices,
	// and feed to XY_poly_fill()
	for (int i = 0; i < numpolys; i++) {
		double px[20], py[20];
		for (int j = 0; j < psize[obji][i]; j++) {
			px[j] = x[obji][con[obji][i][j]];
			py[j] = y[obji][con[obji][i][j]];
		}
		xy_poly_fill(px, py, psize[obji][i], poly_rgb[obji][i]);
	}
}

void center_and_scale(int obji) {
	double biggest[2] = {0, 0};
	double smallest[2] = {0, 0};

	// Check X and Y coordinates
	biggest[0] = x[obji][0];
	biggest[1] = y[obji][0];
	smallest[0] = biggest[0];
	smallest[1] = biggest[1];
	for (int i = 1; i < numpoints; i++) {
		if (x[obji][i] > biggest[0])
			biggest[0] = x[obji][i];
		if (x[obji][i] < smallest[0])
			smallest[0] = x[obji][i];
		if (y[obji][i] > biggest[1])
			biggest[1] = y[obji][i];
		if (y[obji][i] < smallest[1])
			smallest[1] = y[obji][i];
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
		x[obji][i] -= smallest[0] + xsize / 2;
		y[obji][i] -= smallest[1] + ysize / 2;
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
		x[obji][i] *= c;
		y[obji][i] *= c;
	}

	for (int i = 0; i < numpoints; i++) {
		x[obji][i] += screen.x / 2;
		y[obji][i] += screen.y / 2;
	}
}