 #include "FPToolkit.c"
#include "maxpolytools.c"

int swidth, sheight, n;

#define MAXOBJS 10
#define MAXPTS 59000
#define MAXPOLYS 57500

int numpoints;
double x[MAXPTS], y[MAXPTS];
int numpolys;
int numobjs;
int psize[MAXPOLYS];
int con[MAXPOLYS][20];
double poly_rgb[MAXPOLYS][3];

// TODO: modify program such that click_and_save can add up to n polygons. Make
// more buttons, so one can "save."

void click_and_save(double grid_size) {
	float done_area_y = 20;
	float done_area_x = 20;
	int i = 0;
	int j = 0;
	double in[2];
	numpoints = 0;
	numpolys = 0;
	G_rgb(1, 1, 0);
	G_fill_rectangle(0, 0, 500, done_area_y);
	G_wait_click(in);
	// Snapping
	in[0] = floor((in[0] + grid_size / 2) / grid_size) * grid_size;
	in[1] = floor((in[1] + grid_size / 2) / grid_size) * grid_size;
	while (True) {
		con[i][j] = j + numpoints;
		x[j + numpoints] = in[0];
		y[j + numpoints] = in[1];

		G_rgb(0, 1, 1);
		G_circle(in[0], in[1], 3);
		G_wait_click(in);
		// Snapping
		in[0] = floor((in[0] + grid_size / 2) / grid_size) * grid_size;
		in[1] = floor((in[1] + grid_size / 2) / grid_size) * grid_size;

		if (in[1] > done_area_y) {
			G_rgb(0, 1, 1);
			G_line(in[0], in[1], x[j + numpoints], y[j + numpoints]);
			j++;
		} else {
			G_rgb(1, 0, 0);
			G_fill_rectangle(0, 0, done_area_x, done_area_y);
			G_rgb(0, 1, 1);
			G_line(
				x[j + numpoints],
				y[j + numpoints],
				x[0 + numpoints],
				y[0 + numpoints]);
			j++;
			psize[i] = j;
			double rgb[3] = {0, 1, 1};

			// FIXME: polys are not being filled.
			printf("Calling Poly Fill. numpoints: %d. j: %d", numpoints, j);
			sub_xy_poly_fill(x, y, numpoints, numpoints + j, rgb);
			i++;
			numpoints += j;

			j = 0;

			G_wait_click(in);
			in[0] = floor((in[0] + grid_size / 2) / grid_size) * grid_size;
			in[1] = floor((in[1] + grid_size / 2) / grid_size) * grid_size;
			if (in[0] <= done_area_x) {
				G_rgb(0.2, 1, 0.3);
				numpolys = i;
				return;
			}
			G_rgb(1, 1, 0);
			G_fill_rectangle(0, 0, 500, done_area_y);
		}
	}
}

void draw_grid(double swidth, double sheight, int offset) {
	G_rgb(0, 1, 0);
	for (int i = offset; i < swidth; i += offset) {
		G_line(0, i, swidth, i); // x0,y0,x1,y1
		G_line(i, 0, i, sheight);
	}
}

void write_poly(char fname[]) {
	FILE *W;
	W = fopen(fname, "w");

	printf("fopen OK \n");
	// Write number of coordinates
	fprintf(W, "%d\n", numpoints);
	printf("numpoints OK \n");

	// Write X and Y coordinates
	for (int i = 0; i < numpoints; i++) {
		fprintf(W, "%lf %lf\n", x[i], y[i]);
	}
	printf("points OK \n");

	// Write number of polygons
	fprintf(W, "%d", numpolys);
	printf("numpolys OK \n");

	// Write polygon point indices
	for (int i = 0; i < numpolys; i++) {
		fprintf(W, "\n%d\t", psize[i]);
		for (int j = 0; j < psize[i]; j++) {
			fprintf(W, "%d ", con[i][j]);
		}
	}
	printf("polys OK \n");

	fprintf(W, "\n");

	// Get polygon colors
	for (int i = 0; i < numpolys; i++) {
		fprintf(
			W, "\n%lf %lf %lf", poly_rgb[i][0], poly_rgb[i][1], poly_rgb[i][2]);
	}
	fprintf(W, "\n");
}

void execute() {
	int offset = 20;
	swidth = 500;
	sheight = 500;
	G_init_graphics(swidth, sheight);
	G_rgb(0, 0, 0);
	G_clear();
	draw_grid(swidth, sheight, offset);

	G_rgb(1, 0, 0);
	click_and_save(offset);
	G_rgb(0, 1, 0);

	// Prompt for file names
	char fname[100];
	printf("name your .xy file: ");
	scanf("%s", fname);

	write_poly(fname);
}

int main() {
	execute();
}
