/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:43:46 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:44:05 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	set_draw_start_end(t_sprite *sprite)
{
	sprite->height = abs((int)(WINDOW_HEIGHT / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + WINDOW_HEIGHT / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + WINDOW_HEIGHT / 2;
	if (sprite->draw_end_y >= WINDOW_HEIGHT)
		sprite->draw_end_y = WINDOW_HEIGHT - 1;
	sprite->width = abs((int)(WINDOW_HEIGHT / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end_x >= WINDOW_WIDTH)
		sprite->draw_end_x = WINDOW_WIDTH - 1;
}

static void	calculate_sprite_position(t_sprite *sprite, t_render *render)
{
	sprite->dist_x = sprite->pos_x - render->player.pos_x;
	sprite->dist_y = sprite->pos_y - render->player.pos_y;
	sprite->inverse_determinate = 1.0 / (render->camera.plane_x
			* render->player.dir_y - render->player.dir_x
			* render->camera.plane_y);
	sprite->transform_x = sprite->inverse_determinate * (render->player.dir_y
			* sprite->dist_x - render->player.dir_x * sprite->dist_y);
	sprite->transform_y = sprite->inverse_determinate * (-render->camera.plane_y
			* sprite->dist_x + render->camera.plane_x * sprite->dist_y);
	sprite->screen_x = (int)((WINDOW_WIDTH / 2) * (1 + sprite->transform_x
				/ sprite->transform_y));
	set_draw_start_end(sprite);
}

static void	draw_stripe(int x, int y, t_sprite *sprite, t_render *render)
{
	int			d;
	uint32_t	color;

	d = (y) * 256 - WINDOW_HEIGHT * 128 + sprite->height * 128;
	sprite->tex_y = ((d * sprite->img->height) / sprite->height) / 256;
	color = get_pixel(sprite->tex, sprite->tex_x, sprite->tex_y);
	if (color != 0xFF000000)
		set_pixel(render->screen_image, x, y, color);
}

static void	draw_sprite(t_sprite *sprite, t_render *render)
{
	int	stripe;
	int	y;

	stripe = sprite->draw_start_x;
	while (stripe < sprite->draw_end_x)
	{
		sprite->tex_x = (int)(256 * (stripe - (-sprite->width / 2
						+ sprite->screen_x)) * sprite->img->width
				/ sprite->width) / 256;
		if (sprite->transform_y > 0 && stripe > 0 && stripe < WINDOW_WIDTH
			&& sprite->transform_y < render->z_buffer[stripe])
		{
			y = sprite->draw_start_y;
			while (y < sprite->draw_end_y)
				draw_stripe(stripe, y++, sprite, render);
		}
		stripe++;
	}
}

void	render_sprites(t_game *game)
{
	t_render	*render;
	int			i;

	render = &game->render;
	i = 0;
	while (i < render->target_count)
	{
		if (render->targets[i].active == 1)
		{
			calculate_sprite_position(&render->targets[i], render);
			draw_sprite(&render->targets[i], render);
		}
		i++;
	}
	i = 0;
	while (i < render->air_count)
	{
		if (render->air[i].active == 1)
		{
			calculate_sprite_position(&render->air[i], render);
			draw_sprite(&render->air[i], render);
		}
		i++;
	}
}