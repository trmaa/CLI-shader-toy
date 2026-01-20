#include <stdio.h>
#include <stdlib.h>

#define ASCII_MODE false

#define ANSI_LEN 22

#define LIGHT_LEVELS 10

char br_vals[LIGHT_LEVELS] = { ' ', '.', ':', '+', '?', '|', '/', 'O', '8', 'X' };

// pixel_t's format -> "\e[48;2;000;000;000m  "
typedef char pixel_t[ANSI_LEN];

struct screen {
	int w, h;
	pixel_t *px;

	void (*print)(struct screen);
	void (*set_px)(pixel_t *, int);
};

void
screen_print_impl(struct screen scr)
{
	for (int j = 0; j < scr.h; j++) {
		for (int i = 0; i < scr.w; i++)
			printf("%s", scr.px[i + scr.w*j]);
		printf("\e[0m\n");
	}
}

void
screen_set_px_impl(pixel_t *px, int col)
{
	int r = col >> 16 & 0xff;
	int g = col >> 8 & 0xff;
	int b = col & 0xff;

	sprintf(*px, "\e[48;2;%d;%d;%dm  ", r, g, b);

#if ASCII_MODE
	float brightness = (float)(r + g + b) / (3 * 255);

	// clamp
	brightness *= 2;
	if (brightness > 1)
		brightness = 1;

	int id = brightness * (LIGHT_LEVELS-1);

	sprintf(*px, "\e[38;2;%d;%d;%dm%c%c", r, g, b, br_vals[id], br_vals[id]);
#endif
}

struct screen
screen(int w, int h)
{
	struct screen scr = { .w = w, .h = h };
	scr.print = screen_print_impl;
	scr.set_px = screen_set_px_impl;

	int len = w * h;

	scr.px = malloc(len * ANSI_LEN);

	for (int i = 0; i < len; i++)
		scr.set_px(&scr.px[i], 0x55aaff);

	return scr;
}
