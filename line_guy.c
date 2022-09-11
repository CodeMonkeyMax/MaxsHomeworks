#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>

struct Vector2 {
	double in[2];
	double x;
	double y;
};

int main() {
	double swidth = 500;
	double sheight = 500;
	G_init_graphics(swidth, sheight);
	G_rgb(0, 0, 0);
	G_clear();

	double click1[2], click2[2], click3[2], ybounds[2];

	G_rgb(0, 1, 0);
	G_wait_click(click1);
	G_wait_click(click2);

	G_line(click1[0], click1[1], click2[0], click2[1]);

	if (click1[1] > click2[1]) {
		// create reference using "&double bigger[2], smaller[2]" (SHOULD work)
		ybounds[0] = click2[1];
		ybounds[1] = click1[1];
	} else {
		ybounds[0] = click1[1];
		ybounds[1] = click2[1];
	}

	G_rgb(1, 0, 0);
	G_wait_click(click3);

	G_line(0, click3[1], 500, click3[1]);

	printf(
		"y bounds: %4.3lf - %4.3lf. click3 y: %4.3lf\n",
		ybounds[0],
		ybounds[1],
		click3[1]);

	if (click3[1] > ybounds[0] && click3[1] < ybounds[1]) {
		printf("between\n");
		double c, ydiff, i[2];

		c = fabs(click2[0] - click1[0]) / fabs(click2[1] - click1[1]);
		printf("c: %4.3lf\n", c);
		ydiff = click3[1] - ybounds[0];
		i[0] = (ydiff * c) + click1[0];
		i[1] = click3[1];

		G_fill_circle(i[0], i[1], 5);
	}

	G_wait_key();
	G_wait_key();
}