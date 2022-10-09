#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>

struct Vector2 {
	double in[2];
	double x;
	double y;
};

int main(void) {
	printf("Hello World\n");

	// init
	double i;
	double swidth, sheight, r;
	double coords[2][2], diff[2], vec[2];
	struct Vector2 click1, click2, difference, line;
	swidth = 600;
	sheight = 600;
	G_init_graphics(swidth, sheight);
	G_clear(0.3, 0.3, 0.4);

	G_rgb(0.95, 0.2, 0.7);
	G_wait_click(coords[0]); // input 1
	click1.x = coords[0][0];
	click1.y = coords[0][1];
	G_fill_circle(click1.x, click1.y, 3);

	G_wait_click(coords[1]); // input 2
	click2.x = coords[1][0];
	click2.y = coords[1][1];

	// math
	diff[0] = coords[0][0] - coords[1][0];
	diff[1] = coords[0][1] - coords[1][1];
	r = diff[0] * diff[0] + diff[1] * diff[1];
	r = sqrt(r);

	// draw circle
	G_circle(coords[0][0], coords[0][1], r);

	// begin bisecting
	// x = cos(theta), y = sin(theta)
	i = 0;
	while (i < 32) {
		float t;
		t = i * 2 * (3.1415926 / 32);
		line.x = r * cos(t) + click1.x;
		line.y = r * sin(t) + click1.y;
		G_line(click1.x, click1.y, line.x, line.y);
		i++;
	}

	int key;
	key = G_wait_key();

	return 0;
}
