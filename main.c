#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.c"

void
shader(struct screen *scr, float time, int i, int j)
{
	int col, r, g;

	g = 255 * j / (scr->h - 1);
	r = 255 * i / (scr->w - 1);

	col = 100 * sin(time);

	if (col < 0)
		col *= -1;

	col |= g << 8;
	col |= r << 16;

	scr->set_px(&scr->px[i + j * scr->w], col);
}

int
main(void)
{
	struct screen scr = screen(40, 20);

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
