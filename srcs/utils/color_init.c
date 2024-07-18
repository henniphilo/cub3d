#include "../../incl/cub3d.h"


void	put_pixel(mlx_image_t *img, int x, int y, t_color color)
{
	int		pixel_i;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	pixel_i = (y * img->width + x) * 4;
	img->pixels[pixel_i] = color.r;
	img->pixels[pixel_i + 1] = color.g;
	img->pixels[pixel_i + 2] = color.b;
	img->pixels[pixel_i + 3] = color.a;
}

void	put_pixel_double(mlx_image_t *img, double x, double y, t_color color)
{
	int		pixel_i;
	int		ix;
	int		iy;

	ix = (int)x;
	iy = (int)y;

	if (ix < 0 || ix >= (int)img->width || iy < 0 || iy >= (int)img->height)
		return ;
	pixel_i = (iy * img->width + ix) * 4;
	img->pixels[pixel_i] = color.r;
	img->pixels[pixel_i + 1] = color.g;
	img->pixels[pixel_i + 2] = color.b;
	img->pixels[pixel_i + 3] = color.a;
}

static int	get_color_value(const char *color_str, int *index)
{
	int	value;

	value = 0;
	while( !ft_isdigit(color_str[*index]) && color_str[*index] != '\0')
		(*index)++;
	while (ft_isdigit(color_str[*index]))
	{
		value = value * 10 + (color_str[*index] - '0');
		(*index)++;
	}
	return (value);
}

int	get_color_int(const char *color_str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = get_color_value(color_str, &i);
	g = get_color_value(color_str, &i);
	b = get_color_value(color_str, &i);
	return ((r << 16) | (g << 8) | b);
}

t_color	int_to_color(int color)
{
	t_color	convert;

	convert.r = (color >> 16) & 0xFF;
	convert.g = (color >> 8) & 0xFF;
	convert.b = color & 0xFF;
	convert.a = 255;
	return (convert);
}
