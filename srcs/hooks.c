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


static void	player_no_one(t_game *game, int y, int x)
{
	int		pos_x;
	int		pos_y;
	t_color	c_floor = {255, 255, 255, 255};
	t_color	c_player = {0, 0, 255, 255};

	pos_x = game->map.player.pos_x;
	pos_y = game->map.player.pos_y;
	put_block(game->img, c_floor, pos_x, pos_y);
	if (game->map.map[pos_y + y][pos_x + x] != '1')
	{
		pos_y += y;
		pos_x += x;
	}
	printf("put block in y %d und x %d \n", pos_y, pos_x);
	put_block(game->img, c_player, pos_x, pos_y);
	game->map.player.pos_x = pos_x;
	game->map.player.pos_y = pos_y;
	//printf("player direction: %c \n", game->map.player.direction);
	//draw_dir(game, pos_x, pos_y, c_player);
}

static int	get_y(mlx_key_data_t key)
{
	if (key.key == MLX_KEY_UP || key.key == MLX_KEY_W)
	{
		return (-1);
	}
	else if (key.key == MLX_KEY_DOWN || key.key == MLX_KEY_S)
	{
		return (1);
	}
	else
		return (0);
}

static int	get_x( mlx_key_data_t key)
{
	if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_A)
	{
		return (-1);
	}
	else if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_D)
	{
		return (1);
	}
	else
		return (0);
}


void	key_hook_(mlx_key_data_t keydata, void *param)
{
	t_game			*game_data;
	t_render_data	*render_data;
	t_map			map_data;
	int			x;
	int			y;

	x = 0;
	y = 0;
	game_data = (t_game *)param;
	render_data = &game_data->render_data;
	map_data = game_data->map;
	if (keydata.action == MLX_RELEASE)
	{
		y = get_y(keydata); //in double damit weiche bewegungen
		x = get_x(keydata);
	//	game_data->map.player.direction = get_direction(keydata, game_data->map.player.direction);
		player_no_one(game_data, y, x);
	}
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
	mini_map_to_screen(game_data);
}
