/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:47 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 14:52:17 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	init_target(t_game *game, double x, double y, int id)
{
	game->render_data.targets[id].active = 1;
	game->render_data.targets[id].pos_x = x + 0.5;
	game->render_data.targets[id].pos_y = y + 0.5;
	game->render_data.targets[id].tex = game->visual_res.target;
	game->render_data.targets[id].img = mlx_texture_to_image(game->mlx_ptr,
			game->visual_res.target);
}

static void	init_door(t_game *game, double x, double y, int id)
{
	game->render_data.doors[id].active = 1;
	game->render_data.doors[id].pos_x = x + 0.5;
	game->render_data.doors[id].pos_y = y + 0.5;
	game->render_data.doors[id].tex = game->visual_res.door;
	game->render_data.doors[id].img = mlx_texture_to_image(game->mlx_ptr,
			game->visual_res.door);
}

static void	init_air(t_game *game, double x, double y, int id)
{
	game->render_data.oxygen_tanks[id].active = 1;
	game->render_data.oxygen_tanks[id].pos_x = x + 0.5;
	game->render_data.oxygen_tanks[id].pos_y = y + 0.5;
	game->render_data.oxygen_tanks[id].tex = game->visual_res.air;
	game->render_data.oxygen_tanks[id].img = mlx_texture_to_image(game->mlx_ptr,
			game->visual_res.air);
}

static void	init_count(t_game *game)
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
				game->render_data.count_target += 1;
			else if (game->map_data.map[y][x] == 'D')
				game->render_data.count_door += 1;
			else if (game->map_data.map[y][x] == 'L')
				game->render_data.count_oxy += 1;
			x++;
		}
		y++;
	}
}

void	check_sprites(t_game *game, t_render_data *render_data, int sprite_type)
{
	t_sprite	*sprite_array;
	int			sprite_count;
	int			i;

	if (sprite_type == 0) // Checking door sprites
	{
		sprite_array = render_data->doors;
		sprite_count = game->render_data.count_door;
	}
	if (sprite_type == 2) // Checking air sprites
	{
		sprite_array = render_data->oxygen_tanks;
		sprite_count = game->render_data.count_oxy;
	}
	else // Checking target sprites
	{
		sprite_array = render_data->targets;
		sprite_count = game->render_data.count_target;
	}
	i = 0;
	while (i < sprite_count)
	{
		switch (sprite_type)
		{
		case 0: // Example case for doors
			if (sprite_array[i].active)
				printf("Door at (%.2f, %.2f) is closed\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Door at (%.2f, %.2f) is open\n", sprite_array[i].pos_x,
					sprite_array[i].pos_y);
			break ;
		case 1: // Example case for targets
			if (sprite_array[i].active)
				printf("Target at (%.2f, %.2f) is not acquired\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Target at (%.2f, %.2f) is acquired\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			break ;
		case 2: // Example case for targets
			if (sprite_array[i].active)
				printf("Air at (%.2f, %.2f) is not caught\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Air at (%.2f, %.2f) is caught, you have %d tanks\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y,
					game->render_data.count_oxy_caught);
			break ;
		// Add other cases as needed for different sprite types
		default:
			printf("Unknown sprite type at (%.2f, %.2f)\n",
				sprite_array[i].pos_x, sprite_array[i].pos_y);
			break ;
		}
		i++;
	}
}

void	init_sprites(t_game *game)
{
	int				x;
	int				y;
	int				i;
	int				j;
	int				h;
	t_render_data	*render_data;

	init_count(game);
	game->render_data.targets = ft_calloc(game->render_data.count_target + 1,
			sizeof(t_sprite));
	game->render_data.doors = ft_calloc(game->render_data.count_door + 1,
			sizeof(t_sprite));
	game->render_data.oxygen_tanks = ft_calloc(game->render_data.count_oxy + 1,
			sizeof(t_sprite));
	i = 0;
	j = 0;
	y = 0;
	h = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			if (i < game->render_data.count_target
				&& game->map_data.map[y][x] == 'T')
			{
				init_target(game, x, y, i);
				i += 1;
			}
			if (j < game->render_data.count_door
				&& game->map_data.map[y][x] == 'D')
			{
				init_door(game, x, y, j);
				j += 1;
			}
			if (h < game->render_data.count_oxy
				&& game->map_data.map[y][x] == 'L')
			{
				init_air(game, x, y, h);
				h += 1;
			}
			x++;
		}
		y++;
	}
	render_data = &game->render_data;
	check_sprites(game, render_data, 0);
	check_sprites(game, render_data, 1);
	check_sprites(game, render_data, 2);
}
