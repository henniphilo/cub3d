#include "../incl/cub3d.h"

void	draw_line(int x, t_render_data *render_data, mlx_image_t *image, mlx_texture_t *tex)
{
	t_color		color = {0, 0, 155, 255};
	t_color		color_side = {100, 0, 155, 255};
	t_raycast	*raycast;
	int			y;
	int			texY;

	raycast = &render_data->raycast;

	if (render_data->flag_side == 1)
		color = color_side;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		texY = (int)render_data->raycast.tex_pos;
		render_data->raycast.tex_pos += render_data->raycast.tex_step_size;
		if (tex)
		{
			uint32_t color_tex = ((uint32_t*)tex->pixels)[tex->width * texY + render_data->raycast.tex_x];
			uint8_t r = (color_tex >> 24) & 0xFF;
			uint8_t b = (color_tex >> 16) & 0xFF;
			uint8_t g = (color_tex >> 8) & 0xFF;
			uint8_t a = (color_tex >> 0) & 0xFF;
			if (r != 0 || g != 0 || b != 0)
			{
				image->pixels[(y * image->width + image->width - 1 - x) * 4 + 0] = a;
				image->pixels[(y * image->width + image->width - 1 - x) * 4 + 1] = g;
				image->pixels[(y * image->width + image->width - 1 - x) * 4 + 2] = b;
				image->pixels[(y * image->width + image->width - 1 - x) * 4 + 3] = r;
			}
		}
		else
		{
			image->pixels[(y * image->width + x) * 4 + 0] = color.r;
			image->pixels[(y * image->width + x) * 4 + 1] = color.g;
			image->pixels[(y * image->width + x) * 4 + 2] = color.b;
			image->pixels[(y * image->width + x) * 4 + 3] = color.a;
		}
		y++;
	}
}
