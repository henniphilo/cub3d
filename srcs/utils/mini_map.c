/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:49 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 17:52:30 by hwiemann         ###   ########.fr       */
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

static t_color	choose_color(t_game *game, int x, int y)
{
	char		tile;

	tile = game->map_data.map[y][x];

	if (tile == ' ' || tile == '\n' || (tile == !game->map_data.first_dir && tile != '0'
		&& tile != 'L' && tile != 'D' && tile != 'T' && tile != '1'))
		return (C_TRANSPARENT);
	if (tile == '1')
		return (C_WALL);
	else if (tile == 'T' && is_target(game, &game->render_data, x, y))
		return (C_TARGET);
	else if (tile == 'L' && is_air(game, &game->render_data, x, y))
		return (C_AIR);
	else if (tile == 'D' && is_door(game, &game->render_data, x, y))
		return (C_DOOR);
	else
		return (C_FLOOR);
}

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color		color;
	bool		should_draw;

	color = choose_color(game, x, y);
	should_draw = (color.a != 0);
	if (should_draw)
		put_block_double(img, color, x, y);
}
