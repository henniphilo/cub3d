#include "../incl/cub3d.h"

static void	move(t_map map_data,
		t_render_data *render_data, int direction)
{
	t_player	*player;

	player = &render_data->player;
	if (map_data.map[(int)(player->pos_x + player->dir_x
			* MOVE_SPEED)][(int)player->pos_y] == '0')
		player->pos_x += player->dir_x * MOVE_SPEED
			* direction;
	if (map_data.map[(int)player->pos_x][(int)(player->pos_y
			+ player->dir_y * MOVE_SPEED)] == '0')
		player->pos_y += player->dir_y * MOVE_SPEED
			* direction;
}

static void	rotate(t_render_data *render_data, int direction)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*player;
	t_camera	*camera;

	player = &render_data->player;
	camera = &render_data->camera;
	old_dir_x = player->dir_x;
	player->dir_x
		= player->dir_x * cos(ROT_SPEED * direction)
		- player->dir_y * sin(ROT_SPEED * direction);
	player->dir_y
		= old_dir_x * sin(ROT_SPEED * direction)
		+ player->dir_y * cos(ROT_SPEED * direction);
	old_plane_x = camera->plane_x;
	camera->plane_x = camera->plane_x * cos(ROT_SPEED * direction)
		- camera->plane_y * sin(ROT_SPEED * direction);
	camera->plane_y = old_plane_x * sin(ROT_SPEED * direction)
		+ camera->plane_y * cos(ROT_SPEED * direction);
}

void	key_hook_(mlx_key_data_t keydata, void *param)
{
	t_game			*game_data;
	t_render_data	*render_data;
	t_map			map_data;

	game_data = (t_game *)param;
	render_data = &game_data->render_data;
	map_data = game_data->map;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
		{
			move(map_data, render_data, 1);ft_putendl_fd("W", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_S)
		{
			move(map_data, render_data, -1);ft_putendl_fd("S", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_A)
		{
			rotate(render_data, 1);ft_putendl_fd("A", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_D)
		{
			rotate(render_data, -1);ft_putendl_fd("D", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game_data->mlx_ptr);
	}
}

void	loop_hook(void *param)
{
	t_game	*game_data = (t_game *)param;
	render_image(game_data);
}