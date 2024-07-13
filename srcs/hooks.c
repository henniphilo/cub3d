#include "../incl/cub3d.h"

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_game			*game;
	t_render_data	*render_data;

	(void)xdelta;
	game = (t_game *)param;
	render_data = &game->render_data;
	if (ydelta > 0)
		rotate(render_data, 1);
	else if (ydelta < 0)
		rotate(render_data, -1);
}

void	key_hook_(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	t_render_data	*render_data;
	t_map_data		*map_data;

	game = (t_game *)param;
	render_data = &game->render_data;
	map_data = &game->map_data;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			free_data(game);
			mlx_close_window(game->mlx_ptr);
		}
		if (keydata.key == MLX_KEY_SPACE)
		{
			open_doors(game, render_data, map_data);
			ft_putendl_fd("SPACE", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_X)
		{
			get_target(game, map_data);
			ft_putendl_fd("X", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_Z)
		{
			get_air(game, map_data);
			ft_putendl_fd("Z", STDERR_FILENO);
		}
		render_data->flag_render = 1;
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT
		|| keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
		{
			player_n1_move(game, map_data, render_data, 1);
			ft_putendl_fd("W", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_S)
		{
			player_n1_move(game, map_data, render_data, -1);
			ft_putendl_fd("S", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_A)
		{
			player_n1_sideways(game, map_data, render_data, -1);
			ft_putendl_fd("A", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_D)
		{
			player_n1_sideways(game, map_data, render_data, 1);
			ft_putendl_fd("D", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_LEFT)
		{
			rotate(render_data, 1);
			//			ft_putendl_fd("Left", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_RIGHT)
		{
			rotate(render_data, -1);
			ft_putendl_fd("Right", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(game->mlx_ptr);
		}
		if (keydata.key == MLX_KEY_SPACE)
		{
			open_doors(game, render_data, map_data);
			ft_putendl_fd("SPACE", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_X)
		{
			get_target(game, map_data);
			ft_putendl_fd("X", STDERR_FILENO);
		}
	}
}

void	loop_hook(void *param)
{
	t_game	*game;

	// if (game->render_data.flag_hit_target == 1)
	// {
	// 	if (!is_get_target(game, &game->render_data,
	// 		game->render_data.ray.grid_pos_x, game->render_data.ray.grid_pos_y))
	// }
	int		render_flag;

	game = (t_game *)param;
	render_flag = game->render_data.flag_render;
	if (render_flag)// || game->img->pixels[0] == 0)
	{
		if (game->air_caught == 0)
			mlx_put_string(game->mlx_ptr, " You need air! Find the tank!", 100, 0);
		else
		{
			print_got_air(game);
		}
		render_worldmap(game);
		calculate_sprite_position(game);
		mini_map_to_screen(game);
		render_flag = 0;
	}
	
	
	// if (game->air_caught != 0)
	// {
	// 	add_look(game, game->visual_res.bubbles_img, 0, WINDOW_HEIGHT
	// 		/ 2);
	// 	add_look(game, game->visual_res.bubbles_img, WINDOW_HEIGHT / 2,
	// 		WINDOW_HEIGHT);
	// }
}
