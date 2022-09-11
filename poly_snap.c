#include "FPToolkit.c"

int swidth, sheight;

void print_poly(double x[], double y[], int n) {
	int i;
	printf("\n");
	printf("%d\n", n);
	for (i = 0; i < n; i++) {
		printf("%7.2lf %7.2lf\n", x[i], y[i]);
	}
	printf("\n");
}

double polygon_perimeter(double x[], double y[], int n) {
	double a, b, c, p;
	int i, j;
graph_
	p = 0.0;
	for (i = 0; i < n; i++) {
		j = i + 1;
		if (j == n) {
			j = 0;
		}
		a = x[j] - x[i];
		b = y[j] - y[i];
		c = sqrt(a * a + b * b);
		p += c;
	}

	return p;
}

int click_and_save(double x[], double y[], double offset) {
	float done_area_y = 20;
	G_fill_rectangle(0, 0, 500, done_area_y);
	int i = 0;
	double in[2];
	G_wait_click(in);
	in[0] = floor((in[0] + offset / 2) / offset) * offset;
	in[1] = floor((in[1] + offset / 2) / offset) * offset;
	while (in[1] > done_area_y) {
		x[i] = in[0];
		y[i] = in[1];
		G_circle(in[0], in[1], 3);
		G_wait_click(in);

		// The magic numbers
		in[0] = floor((in[0] + offset / 2) / offset) * offset;
		in[1] = floor((in[1] + offset / 2) / offset) * offset;
		
		if (in[1] > done_area_y) {
			G_line(in[0], in[1], x[i], y[i]);
		} else {
			G_line(x[i], y[i], x[0], y[0]);
		}
		i++;
	}
	return i;
}

void draw_grid(double swidth, double sheight, int offset) {
	G_rgb(0, 1, 0);
	for (int i = offset; i < swidth; i += offset) {
		G_line(0, i, swidth, i); // x0,y0,x1,y1
		G_line(i, 0, i, sheight);
	}
}

void execute() {
	double xp[1000], yp[1000], p1;
	int m;
	double P[2];

	int offset = 20;

	swidth = 500;
	sheight = 500;
	G_init_graphics(swidth, sheight);
	G_rgb(0, 0, 0);
	G_clear();

	draw_grid(swidth, sheight, offset);

	G_rgb(1, 0, 0);
	m = click_and_save(xp, yp, offset);

	p1 = polygon_perimeter(xp, yp, m);
	printf("p1 = %lf \n", p1);

	G_rgb(0, 1, 0);

	G_fill_polygon(xp, yp, m);

	G_wait_key();

	print_poly(xp, yp, m);
}

int main() {
	execute();
}
