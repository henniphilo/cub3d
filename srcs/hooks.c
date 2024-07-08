#include "../incl/cub3d.h"

static void	move(t_game *game, t_map map_data,
		t_render_data *render_data, int direction)
{
	t_player	*player;

	player = &render_data->player;
//	printf("map [%c][%c]\n", map_data.map[(int)(player->pos_x + player->dir_x
//			* MOVE_SPEED)][(int)player->pos_y], map_data.map[(int)player->pos_x][(int)(player->pos_y
//			+ player->dir_y * MOVE_SPEED)]);
	if (map_data.map[(int)(player->pos_x + player->dir_x
			* MOVE_SPEED)][(int)player->pos_y] == '0' || map_data.map[(int)(player->pos_x + player->dir_x
			* MOVE_SPEED)][(int)player->pos_y] == game->look.first_dir)
		player->pos_x += player->dir_x * MOVE_SPEED
			* direction;
	if (map_data.map[(int)player->pos_x][(int)(player->pos_y
			+ player->dir_y * MOVE_SPEED)] == '0' || map_data.map[(int)player->pos_x][(int)(player->pos_y
			+ player->dir_y * MOVE_SPEED)] == game->look.first_dir)
		player->pos_y += player->dir_y * MOVE_SPEED
			* direction;
	printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y); // Debugging
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


static void	player_n1_move(t_game *game, t_map map_data,
		t_render_data *render_data, int direction)
{
	t_color		c_floor = {255, 255, 255, 255};
	t_color		c_player = {0, 0, 255, 255};
	t_player	*player;

	player = &game->render_data.player;
//	printf("pos_x %.2f und pos_y %.2f \n", player->pos_x, player->pos_y);
	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	move(game, map_data, render_data, direction);
	if ((map_data.map[(int)(player->pos_x + player->dir_x
			* MOVE_SPEED)][(int)player->pos_y] == '0' || map_data.map[(int)(player->pos_x + player->dir_x
			* MOVE_SPEED)][(int)player->pos_y] == game->look.first_dir) && (map_data.map[(int)player->pos_x][(int)(player->pos_y
			+ player->dir_y * MOVE_SPEED)] == '0' || map_data.map[(int)player->pos_x][(int)(player->pos_y
			+ player->dir_y * MOVE_SPEED)] == game->look.first_dir))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);

		//printf("player direction: %c \n", game->map.player.direction);
	//draw_dir(game, pos_x, pos_y, c_player);
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
			player_n1_move(game_data, map_data, render_data, 1);
			//move(map_data, render_data, 1);
			ft_putendl_fd("W", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_S)
		{
			player_n1_move(game_data, map_data, render_data, -1);
			//move(map_data, render_data, -1);
			ft_putendl_fd("S", STDERR_FILENO);
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
		{
			free_data(game_data);
			mlx_close_window(game_data->mlx_ptr);
		}
	}
}

void	loop_hook(void *param)
{
	t_game	*game_data = (t_game *)param;
	//t_player	*player = &game_data->render_data.player;

	// if ((int)player->prev_pos_x != (int)player->pos_x ||
	// 	(int)player->prev_pos_y != (int)player->pos_y)
	// {
	// 	player->prev_pos_x = player->pos_x;
	// 	player->prev_pos_y = player->pos_x;
//	}
	render_image(game_data);
	mini_map_to_screen(game_data);
}
