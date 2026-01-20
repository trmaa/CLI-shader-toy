#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.c"

void
shader(struct screen *scr, float time, int i, int j)
{

	float viewport = (float)scr->w / scr->h;

	float u = ((float)i / (scr->w-1))*2 - 1;
	float v = ((float)j / (scr->h-1))*2 - 1;

	u *= viewport;

	float rad = (u*u + v*v) / (1 + viewport*viewport); // from 0 to 1;

	int col = 0, r = 0, g = 0, b = 0;

/*
 * This is the only part of the code that you should touch to use the tool.
 * Modify the shader to your will to render any image you like!
 */
	r = 255 * (((float)i / (scr->w-1))*2 - 1);
	g = 255 * (((float)j / (scr->h-1))*2 - 1);

	r *= rad * sin(time);
	g *= rad * sin(time);

	if (r < 0)
		r *= -1;
	if (g < 0)
		g *= -1;

	if (rad < 0.05) {
		r = 255;
		g = 255;
		b = 255;
	}
/*
 * The end.
 */

	col = b;
	col += g << 8;
	col += r << 16;

	scr->set_px(&scr->px[i + j * scr->w], col);
}

int
main(void)
{
	struct screen scr = screen(60, 30);

	float time;

	while (1) {
		system("clear");

		time += 0.01f;

		for (int j = 0; j < scr.h; j++)
			for (int i = 0; i < scr.w; i++)
				shader(&scr, time, i, j);

		scr.print(scr);	

		usleep(16667);
	}
}
