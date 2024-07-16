/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:49 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 14:50:00 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game	*mini_map_init(t_game *game)
{
	int			i;

	i = 0;
	fill_half(game, game->visual_res.c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game, game->visual_res.c_floor, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->img, 0, 0);
	return (game);
}

void	mini_map_to_screen(t_game *game)
{
	int		x;
	int		y;
	t_color c_player = {0, 0, 255, 255};

	y = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			draw_mini_map(game, game->img, x, y);
			x++;
		}
		y++;
	}
	put_block_double(game->img, c_player,
		game->render_data.player.pos_x, game->render_data.player.pos_y);
}

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color		wall = {0,0,0,255};
	t_color		air = {200,0,100,255};
	t_color		target = {150, 150, 0, 255};
	t_color		door = {100, 80, 150, 255};
	t_color		floor = {255, 255, 255, 255};
	t_color		color;
	bool		should_draw;

	should_draw = true;
	if (game->map_data.map[y][x] == '1')
		color = wall;
	else if (game->map_data.map[y][x] == 'T')
	{
		if (is_target(game, &game->render_data, x, y))
			color = target;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'L')
	{
		if (is_air(game, &game->render_data, x, y))
			color = air;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'D')
	{
		if (is_door(game, &game->render_data, x, y))
			color = door;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'N' || game->map_data.map[y][x] == 'E'
		|| game->map_data.map[y][x] == 'W' || game->map_data.map[y][x] == 'S'
		|| game->map_data.map[y][x] == '0')
		color = floor;
	else
		should_draw = false;
	if (should_draw == true)
		put_block_double(img, color, x, y);
}
