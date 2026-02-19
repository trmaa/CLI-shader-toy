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

	float sin = sinf(time);
	float cos = cosf(time);

	if (sin < 0)
		sin *= -1;
	if (cos < 0)
		cos *= -1;

	int col = 0, r = 0, g = 0, b = 0;

/*
 * This is the only part of the code that you should touch to use the tool.
 * Modify the shader to your will to render any image you like!
 */
	r = 255 * (((float)i / (scr->w-1))*2 - 1);
	g = 255 * (((float)j / (scr->h-1))*2 - 1);

	r *= rad * sin;
	g *= rad * sin;

	if (r < 0)
		r *= -1;
	if (g < 0)
		g *= -1;

	b = 255 * rad * cos;

	if (rad < sin * 0.1 && rad > sin * 0.05) {
		r = 255;
		g = 255 * cos;
		b = 255 * cos;
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

	for (;;) {
		system("clear");

		time += 0.01f;

		for (int j = 0; j < scr.h; j++)
			for (int i = 0; i < scr.w; i++)
				shader(&scr, time, i, j);

		scr.print(scr);	

		usleep(16667);
	}
}
