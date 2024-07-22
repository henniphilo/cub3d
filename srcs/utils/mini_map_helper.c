/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 14:45:46 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	put_block(mlx_image_t *img, t_color color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i <= SSIZE)
	{
		j = 0;
		while (j <= SSIZE)
		{
			put_pixel(img, x * SSIZE + i, y * SSIZE + j, color);
			j++;
		}
		i++;
	}
}

void	put_block_double(mlx_image_t *img, t_color color, double x, double y)
{
	int		i;
	int		j;
	double	ix;
	double	iy;

	i = 0;
	ix = (x * SSIZE);
	iy = (y * SSIZE);
	while (i < SSIZE)
	{
		j = 0;
		while (j < SSIZE)
		{
			put_pixel_double(img, ix + i, iy + j, color);
			j++;
		}
		i++;
	}
}

static void	init_bg_img(t_game *game)
{
	game->render.res.bubbles = mlx_load_png(BUBBLE_PATH);
	game->render.res.bubbles_img = mlx_texture_to_image(game->mlx_ptr,
			game->render.res.bubbles);
	mlx_delete_texture(game->render.res.bubbles);
}

void	fill_half(t_game *game, t_color color, int start_y, int end_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < (int)game->render.screen_image->width)
		{
			put_pixel(game->render.screen_image, x, y, color);
			x++;
		}
		y++;
	}
	init_bg_img(game);
}
