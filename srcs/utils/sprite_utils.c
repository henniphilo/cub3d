/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:25 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/21 14:38:28 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	init_sprites_count(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			if (game->map_data.map[y][x] == 'T')
				game->render_data.target_count += 1;
			else if (game->map_data.map[y][x] == 'D')
				game->render_data.door_count += 1;
			else if (game->map_data.map[y][x] == 'L')
				game->render_data.air_count += 1;
			x++;
		}
		y++;
	}
}

void	set_textures(int sprite_count, t_sprite *sprites_arr,
		mlx_texture_t *texture, t_game *game)
{
	int	i;

	i = 0;
	while (i < sprite_count)
	{
		sprites_arr[i].tex = texture;
		sprites_arr[i].img = mlx_texture_to_image(game->mlx_ptr, texture);
		i++;
	}
}

void	set_position(int sprite_count, t_sprite *sprites_arr, char type,
		t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < game->map_data.y_axis && i < sprite_count)
	{
		x = 0;
		while (x < game->map_data.x_axis[y] && i < sprite_count)
		{
			if (game->map_data.map[y][x] == type)
			{
				sprites_arr[i].pos_x = x + 0.5;
				sprites_arr[i].pos_y = y + 0.5;
				sprites_arr[i].active = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}
