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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	t_render_data	*render_data;
	t_map_data		*map_data;

	game = (t_game *)param;
	render_data = &game->render_data;
	map_data = &game->map_data;
	if (keydata.action == MLX_PRESS)
	{
		keys_act(game, keydata);
		render_data->flag_render = 1; //was ist das??? diese hier sehr gut 
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		keys_rotate(keydata, render_data);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT
		|| keydata.action == MLX_RELEASE)
		keys_walk(game, keydata);
}

void	keys_walk(t_game *game, mlx_key_data_t keydata)
{
	t_render_data	*render_data;
	t_map_data		*map_data;

	render_data = &game->render_data;
	map_data = &game->map_data;
	if (keydata.key == MLX_KEY_W)
		player_n1_move(game, map_data, render_data, 1);
	if (keydata.key == MLX_KEY_S)
		player_n1_move(game, map_data, render_data, -1);
	if (keydata.key == MLX_KEY_A)
		player_n1_sideways(game, map_data, render_data, 1);
	if (keydata.key == MLX_KEY_D)
		player_n1_sideways(game, map_data, render_data, -1);
	if (game->render_data.count_oxy_caught != 0)
		create_bubbles(game);
}

void	keys_rotate(mlx_key_data_t keydata, t_render_data *render_data)
{
	if (keydata.key == MLX_KEY_LEFT)
		rotate(render_data, -1);
	if (keydata.key == MLX_KEY_RIGHT)
		rotate(render_data, 1);
}

void	keys_act(t_game *game, mlx_key_data_t keydata)
{
	t_render_data	*render_data;
	t_map_data		*map_data;

	render_data = &game->render_data;
	map_data = &game->map_data;
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
}

void	loop_hook(void *param)
{
	t_game	*game;
	int		render_flag;

	game = (t_game *)param;
	render_flag = game->render_data.flag_render;
	if (render_flag)// || game->img->pixels[0] == 0)
	{
		if (game->render_data.count_fish_caught != 0)
		{
			mlx_put_string(game->mlx_ptr, " You caught fish: ", 700, 0);
			mlx_put_string(game->mlx_ptr, ft_itoa(game->render_data.count_fish_caught), 800, 0);
		}
		if (game->render_data.count_oxy_caught == 0)
			mlx_put_string(game->mlx_ptr, " You need air! Hurry! Find the tank!", 400, 0);
		else
			print_got_air(game);
		render_worldmap(game);
		render_sprites(game);
		mini_map_to_screen(game);
		render_flag = 0;
	}
}
