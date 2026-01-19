#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "screen.c"

int
main(void)
{
	struct screen scr = screen(40, 20);

	while (1) {
		clock_t start = clock();

		system("clear");	

		int col, r, g;
		for (int j = 0; j < scr.h; j++) {
			g = 255 * j / (scr.h - 1);

			for (int i = 0; i < scr.w; i++) {
				r = 255 * i / (scr.w - 1);

				col = 0;
				col |= g << 8;
				col |= r << 16;

				scr.set_px(&scr.px[i + j * scr.w], col);
			}
		}

		scr.print(scr);	

		usleep(16667);

		clock_t end = clock();

		double dtime = end - start;
		dtime /= 1000;

		int fps = 1/dtime;

		printf("fps: %d", fps);
	}
}
