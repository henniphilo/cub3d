/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:41:14 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/23 15:41:40 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	color_textures(t_game *game, mlx_texture_t *tex, int pixel_index)
{
	uint32_t	color_tex;
	t_color		color;
	uint32_t	tex_pos;
	uint32_t	tex_x;

	tex_pos = (uint32_t)game->render.raycast.tex_pos;
	tex_x = game->render.raycast.tex_x;
	if (tex_pos >= 0 && tex_pos < tex->height && tex_x >= 0
		&& tex_x < tex->width)
	{
		color_tex = ((uint32_t *)tex->pixels)[tex->width * tex_pos + tex_x];
		color.r = (color_tex >> 24) & 0xFF;
		color.g = (color_tex >> 16) & 0xFF;
		color.b = (color_tex >> 8) & 0xFF;
		color.a = (color_tex >> 0) & 0xFF;
		if (color.r != 0 || color.g != 0 || color.b != 0)
		{
			game->render.screen_image->pixels[pixel_index + 0] = color.a;
			game->render.screen_image->pixels[pixel_index + 1] = color.b;
			game->render.screen_image->pixels[pixel_index + 2] = color.g;
			game->render.screen_image->pixels[pixel_index + 3] = color.r;
		}
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

	raycast = &game->render.raycast;
	y = raycast->draw_start;
	if (game->render.flag_side == 1)
		color = game->minimap.cblue;
	while (y < raycast->draw_end)
	{
		pixel_index = (y * game->render.screen_image->width
				+ game->render.screen_image->width - 1 - x) * 4;
		raycast->tex_pos += raycast->tex_step_size;
		if (tex)
			color_textures(game, tex, pixel_index);
		else
			apply_color(image, color, (y * image->width + x) * 4);
		y++;
	}
}
