#include "../incl/cub3d.h"

static int	is_door_open(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if((int)render_data->doors[i].pos_x == x && (int)render_data->doors[i].pos_y == y)
			return(render_data->doors[i].open_door);
		i++;
	}
	return (0);
}

static int	is_get_target(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->target_count)
	{
		if((int)render_data->targets[i].pos_x == x && (int)render_data->targets[i].pos_y == y)
			return(render_data->targets[i].got_target);
		i++;
	}
	return (0);
}

static void	sideways(t_game *game, t_map_data map_data, t_render_data *render_data, int direction)
{
	t_player	*player;
	double		side_dir_x;
	double		side_dir_y;

	player = &render_data->player;
	side_dir_x = player->dir_y;
	side_dir_y = -player->dir_x;

	if (map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == '0'
		|| map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == game->map_data.first_dir
		|| (map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == 'D' &&
			is_door_open(game, render_data, (int)(player->pos_x + side_dir_x * MOVE_SPEED * direction), (int)player->pos_y))
		|| (map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == 'T' &&
			is_get_target(game, render_data, (int)(player->pos_x + side_dir_x * MOVE_SPEED * direction), (int)player->pos_y)))
		{
			player->pos_x += side_dir_x * MOVE_SPEED * direction;
		}
	if (map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED * direction)] == '0'
		|| map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED * direction)] == game->map_data.first_dir
		|| (map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED * direction)] == 'D' &&
			is_door_open(game, render_data, (int)player->pos_x, (int)(player->pos_y + side_dir_y * MOVE_SPEED * direction)))
		|| (map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED * direction)] == 'T' &&
			is_get_target(game, render_data, (int)player->pos_x, (int)(player->pos_y + side_dir_y * MOVE_SPEED * direction))))
		{
			player->pos_y += side_dir_y * MOVE_SPEED * direction;
		}
	printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y); // Debugging
}

static void	move(t_game *game, t_map_data map_data,
		t_render_data *render_data, int direction)
{
	t_player	*player;

	player = &render_data->player;
	if (map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == '0'
		|| map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == game->map_data.first_dir
		|| (map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == 'D' &&
			is_door_open(game, render_data, (int)(player->pos_x + player->dir_x * MOVE_SPEED * direction), (int)player->pos_y))
		|| (map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction)][(int)player->pos_y] == 'T' &&
			is_get_target(game, render_data, (int)(player->pos_x + player->dir_x * MOVE_SPEED), (int)player->pos_y)))
		{
			player->pos_x += player->dir_x * MOVE_SPEED * direction;
		}
	if (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)] == '0'
		|| map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)] == game->map_data.first_dir
		|| (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)] == 'D' &&
			is_door_open(game, render_data, (int)player->pos_x, (int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)))
		|| (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)] == 'T' &&
			is_get_target(game, render_data, (int)player->pos_x, (int)(player->pos_y + player->dir_y * MOVE_SPEED * direction))))
		{
			player->pos_y += player->dir_y * MOVE_SPEED * direction;
		}
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


static void	player_n1_sideways(t_game *game, t_map_data map_data,
		t_render_data *render_data, int direction)
{
	t_color		c_floor = {255, 255, 255, 255};
	t_color		c_player = {0, 0, 255, 255};
	t_player	*player;
	double		side_dir_x;
	double		side_dir_y;

	player = &game->render_data.player;
	side_dir_x = player->dir_y;
	side_dir_y = player->dir_x;
	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	sideways(game, map_data, render_data, direction);
	if (((map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED)][(int)player->pos_y] == '0'
		|| map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED)][(int)player->pos_y] == game->map_data.first_dir) &&
		(map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED)] == '0'
		|| map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED)] == game->map_data.first_dir)) ||
		((map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED)][(int)player->pos_y] == 'D' &&
			is_door_open(game, render_data, (int)(player->pos_x + side_dir_x * MOVE_SPEED), (int)player->pos_y))
		|| (map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED)] == 'D' &&
			is_door_open(game, render_data, (int)player->pos_x, (int)(player->pos_y + side_dir_y * MOVE_SPEED))))
		|| ((map_data.map[(int)(player->pos_x + side_dir_x * MOVE_SPEED)][(int)player->pos_y] == 'T' &&
			is_get_target(game, render_data, (int)(player->pos_x + side_dir_x * MOVE_SPEED), (int)player->pos_y)))
		|| (map_data.map[(int)(player->pos_x)][(int)(player->pos_y + side_dir_y * MOVE_SPEED)] == 'T' &&
			is_get_target(game, render_data, (int)player->pos_x, (int)(player->pos_y + side_dir_y * MOVE_SPEED))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
}

static void	player_n1_move(t_game *game, t_map_data map_data,
		t_render_data *render_data, int direction)
{
	t_color		c_floor = {255, 255, 255, 255};
	t_color		c_player = {0, 0, 255, 255};
	t_player	*player;

	player = &game->render_data.player;
	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	move(game, map_data, render_data, direction);
	if (((map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)player->pos_y] == '0'
		|| map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)player->pos_y] == game->map_data.first_dir) &&
		 (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == '0'
		|| map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == game->map_data.first_dir)) ||
		((map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)player->pos_y] == 'D' &&
			is_door_open(game, render_data, (int)(player->pos_x + player->dir_x * MOVE_SPEED), (int)player->pos_y))
		|| (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == 'D' &&
			is_door_open(game, render_data, (int)player->pos_x, (int)(player->pos_y + player->dir_y * MOVE_SPEED)))
		|| ((map_data.map[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)player->pos_y] == 'T' &&
			is_get_target(game, render_data, (int)(player->pos_x + player->dir_x * MOVE_SPEED), (int)player->pos_y))
		|| (map_data.map[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == 'T' &&
			is_get_target(game, render_data, (int)player->pos_x, (int)(player->pos_y + player->dir_y * MOVE_SPEED))))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
}

static void	open_doors(t_game *game, t_render_data *render_data, t_map_data map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	if (render_data->doors->open_door == 0) //problematisch
	{
		i = 0;
		if ((map_data.map[(int)player->pos_x][y] == 'D') || map_data.map[x][(int)player->pos_y] == 'D')
		{
		//	render_data->sprites.open_door = 1;
			while (i < game->door_count)
			{
				if (game->render_data.doors[i].pos_x == x && game->render_data.doors[i].pos_y == y)
				{
					game->render_data.doors[i].open_door = 1;
					printf("door open\n");
					break ;
				}
				i++;
			}
		}
	}
}

static void	get_target(t_game *game, t_render_data *render_data, t_map_data map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	if (render_data->targets->got_target == 0)
	{
		i = 0;
		if ((map_data.map[(int)player->pos_x][y] == 'T') || map_data.map[x][(int)player->pos_y] == 'T')
		{
		//	render_data->sprites.open_door = 1;
			while (i < game->door_count)
			{
				if (game->render_data.targets[i].pos_x == x && game->render_data.doors[i].pos_y == y)
				{
					game->render_data.targets[i].got_target = 1;
					printf("got target\n");
					break ;
				}
				i++;
			}
		}
	}
}


void	key_hook_(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	t_render_data	*render_data;
	t_map_data			map_data;

	game = (t_game *)param;
	render_data = &game->render_data;
	map_data = game->map_data;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE)
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
			ft_putendl_fd("Left", STDERR_FILENO);
		}
		if (keydata.key == MLX_KEY_RIGHT)
		{
			rotate(render_data, -1);
			ft_putendl_fd("Right", STDERR_FILENO);
		}
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
			get_target(game, render_data, map_data);
			ft_putendl_fd("X", STDERR_FILENO);
		}
	}
}

void	loop_hook(void *param)
{
	t_game	*game = (t_game *)param;


	render_image(game);
	if (game->render_data.flag_hit_target == 1)
	{
		if (!is_get_target(game, &game->render_data, game->render_data.ray.grid_pos_x, game->render_data.ray.grid_pos_y))
			calculate_sprite_position(game);
	}
	mini_map_to_screen(game);
}
