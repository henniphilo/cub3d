#include "../../incl/cub3d.h"

uint32_t get_pixel(mlx_texture_t *img, int x, int y)
{
    if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
        return 0xFF000000; // Return black if out of bounds

    return ((uint32_t *)img->pixels)[y * img->width + x];
}

void set_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	uint8_t r;
	uint8_t b;
	uint8_t g;
	uint8_t a;

    if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return;
	r = (color >> 24) & 0xFF;
	b = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	a = (color >> 0) & 0xFF;
	if (r != 0 || g != 0 || b != 0)
	{
		img->pixels[(y * img->width + img->width + 1 - x) * 4 + 0] = a;
		img->pixels[(y * img->width + img->width + 1 - x) * 4 + 1] = g;
		img->pixels[(y * img->width + img->width + 1 - x) * 4 + 2] = b;
		img->pixels[(y * img->width + img->width + 1 - x) * 4 + 3] = r;
	}
}
