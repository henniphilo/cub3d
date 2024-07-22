/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:49 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 12:39:21 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_game	*mini_map_init(t_game *game)
{
	int	i;

	i = 0;
	init_look(game);
	fill_half(game, game->render.res.c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game, game->render.res.c_floor, WINDOW_HEIGHT / 2,
		WINDOW_HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->render.screen_image, 0, 0);
	return (game);
}

void	render_mini_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->minimap.y_axis)
	{
		x = 0;
		while (x < game->minimap.x_axis[y])
		{
			draw_mini_map(game, game->render.screen_image, x, y);
			x++;
		}
		y++;
	}
	put_block_double(game->render.screen_image, game->minimap.cplayer,
		game->render.player.pos_x, game->render.player.pos_y);
}

static t_color	choose_color(t_game *game, int x, int y)
{
	char	tile;

	tile = game->minimap.map[y][x];
	if (tile == ' ' || tile == '\n' 
	// || (tile == !game->minimap.first_dir
	// 		&& tile != '0' && tile != 'L' && tile != 'D' && tile != 'T'
	// 		&& tile != '1')
			)
		return (game->minimap.ctransparent);
	if (tile == '1')
		return (game->minimap.cwall);
	else if (tile == 'T' && is_target(&game->render, x, y))
		return (game->minimap.ctarget);
	else if (tile == 'L' && is_air(&game->render, x, y))
		return (game->minimap.cair);
	else if (tile == 'D' && is_door(&game->render, x, y))
		return (game->minimap.cdoor);
	else
		return (game->minimap.cfloor);
}

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color	color;
	bool	should_draw;

	color = choose_color(game, x, y);
	should_draw = (color.a != 0);
	if (should_draw)
		put_block_double(img, color, x, y);
}
