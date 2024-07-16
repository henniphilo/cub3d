/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:41:14 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 18:22:44 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	color_textures(t_game *game, mlx_texture_t *tex, int x, int y)
{
	uint32_t	color_tex;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	color_tex = ((uint32_t *)tex->pixels)
	[tex->width * (int)game->render_data.raycast.tex_pos
		+ game->render_data.raycast.tex_x];
	r = (color_tex >> 24) & 0xFF;
	g = (color_tex >> 16) & 0xFF;
	b = (color_tex >> 8) & 0xFF;
	a = (color_tex >> 0) & 0xFF;
	if (r != 0 || g != 0 || b != 0)
	{
		game->img->pixels[(y * game->img->width + game->img->width - 1 - x)
			* 4 + 0] = a;
		game->img->pixels[(y * game->img->width + game->img->width - 1 - x)
			* 4 + 1] = b;
		game->img->pixels[(y * game->img->width + game->img->width - 1 - x)
			* 4 + 2] = g;
		game->img->pixels[(y * game->img->width + game->img->width - 1 - x)
			* 4 + 3] = r;
	}
}

static void	apply_color(mlx_image_t *image, t_color color, int x, int y)
{
	image->pixels[(y * image->width + x) * 4 + 0] = color.r;
	image->pixels[(y * image->width + x) * 4 + 1] = color.g;
	image->pixels[(y * image->width + x) * 4 + 2] = color.b;
	image->pixels[(y * image->width + x) * 4 + 3] = color.a;
}

void	draw_line(int x, t_game *game, mlx_image_t *image,
			mlx_texture_t *tex)
{
	t_color		color;
	t_color		color_side;
	t_raycast	*raycast;
	int			y;
	int			tex_y;

	color = C_BLUE;
	color_side = C_SIDE;
	raycast = &game->render_data.raycast;
	y = raycast->draw_start;
	if (game->render_data.flag_side == 1)
		color = color_side;
	while (y < raycast->draw_end)
	{
		tex_y = (int)raycast->tex_pos;
		raycast->tex_pos += raycast->tex_step_size;
		if (tex)
			color_textures(game, tex, x, y);
		else
			apply_color(image, color, x, y);
		y++;
	}
}
