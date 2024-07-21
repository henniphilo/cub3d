/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:41:14 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 12:33:58 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	color_textures(t_game *game, mlx_texture_t *tex, int pixel_index)
{
	uint32_t	color_tex;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	color_tex = ((uint32_t *)tex->pixels)[tex->width
		* (int)game->render_data.raycast.tex_pos
		+ game->render_data.raycast.tex_x];
	r = (color_tex >> 24) & 0xFF;
	g = (color_tex >> 16) & 0xFF;
	b = (color_tex >> 8) & 0xFF;
	a = (color_tex >> 0) & 0xFF;
	if (r != 0 || g != 0 || b != 0)
	{
		game->render_data.screen_image->pixels[pixel_index + 0] = a;
		game->render_data.screen_image->pixels[pixel_index + 1] = b;
		game->render_data.screen_image->pixels[pixel_index + 2] = g;
		game->render_data.screen_image->pixels[pixel_index + 3] = r;
	}
}

static void	apply_color(mlx_image_t *image, t_color color, int pixel_index)
{
	image->pixels[pixel_index + 0] = color.r;
	image->pixels[pixel_index + 1] = color.g;
	image->pixels[pixel_index + 2] = color.b;
	image->pixels[pixel_index + 3] = color.a;
}

void	draw_line(int x, t_game *game, mlx_image_t *image, mlx_texture_t *tex)
{
	t_color		color;
	t_raycast	*raycast;
	int			y;
	int			pixel_index;

	raycast = &game->render_data.raycast;
	y = raycast->draw_start;
	if (game->render_data.flag_side == 1)
		color = game->look.cblue;
	while (y < raycast->draw_end)
	{
		pixel_index = (y * game->render_data.screen_image->width
				+ game->render_data.screen_image->width - 1 - x) * 4;
		raycast->tex_pos += raycast->tex_step_size;
		if (tex)
			color_textures(game, tex, pixel_index);
		else
			apply_color(image, color, (y * image->width + x) * 4);
		y++;
	}
}
