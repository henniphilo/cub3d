#include "../incl/cub3d.h"

int	is_door_open(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if ((int)render_data->doors[i].pos_x == x
			&& (int)render_data->doors[i].pos_y == y)
			return (render_data->doors[i].open_door);
		i++;
	}
	return (0);
}

int	is_get_target(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->target_count)
	{
		if ((int)render_data->targets[i].pos_x == x
			&& (int)render_data->targets[i].pos_y == y)
			return (render_data->targets[i].got_target);
		i++;
	}
	return (0);
}

int	is_get_air(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->air_caught)
	{
		if ((int)render_data->air_sprites[i].pos_x == x
			&& (int)render_data->air_sprites[i].pos_y == y)
			return (render_data->air_sprites[i].got_air);
		i++;
	}
	return (0);
}

static void	sideways(t_game *game, t_map_data *map_data,
		t_render_data *render_data, int direction)
{
	t_player	*player;
	double		side_dir_x;
	double		side_dir_y;
	int			next_x;
	int			next_y;

	player = &render_data->player;
	side_dir_x = (player->dir_y);
	side_dir_y = -(player->dir_x);
	next_x = player->pos_x + side_dir_x * MOVE_SPEED * direction;
	next_y = player->pos_y;
	printf("vorher pos %.2f, pos_y %.2f\n", player->pos_x, player->pos_y);
	printf("side_dir_x %.2f side_dir_y %.2f \n", side_dir_x, side_dir_y);
	printf("player dir_x %.2f player_dir_y %.2f \n", player->dir_x,
		(player->dir_y));
	printf("direction %d \n", direction);
	if (map_data->map[next_y][next_x] == '0'
		|| map_data->map[next_y][next_x] == game->map_data.first_dir
		|| (map_data->map[next_y][next_x] == 'D' && is_door_open(game,
				render_data, next_x, next_y))
		|| (map_data->map[next_y][next_x] == 'T' && is_get_target(game,
				render_data, next_x, next_y)))
	{
		player->pos_x = next_x;
	}
	next_x = player->pos_x;
	next_y = player->pos_y + side_dir_y * MOVE_SPEED * direction;
	if (map_data->map[next_y][next_x] == '0'
		|| map_data->map[next_y][next_x] == game->map_data.first_dir
		|| (map_data->map[next_y][next_x] == 'D' && is_door_open(game,
				render_data, next_x, next_y))
		|| (map_data->map[next_y][next_x] == 'T'
			&& is_get_target(game, render_data, next_x,
				next_y)))
	{
		player->pos_y += side_dir_y * MOVE_SPEED * (direction);
	}
	printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y);
	// Debugging
}

static void	move(t_game *game, t_map_data *map_data, t_render_data *render_data,
		int direction)
{
	t_player	*player;
	double			next_x;
	double			next_y;

	player = &render_data->player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED * direction;
	next_y = player->pos_y;
	if (map_data->map[(int)next_y][(int)next_x] == '0'
		|| map_data->map[(int)next_y][(int)next_x] == game->map_data.first_dir
		|| (map_data->map[(int)next_y][(int)next_x] == 'D' && is_door_open(game,
				render_data, next_x, next_y))
		|| (map_data->map[(int)next_y][(int)next_x] == 'T' && is_get_target(game,
				render_data, next_x, next_y)))
	{
		player->pos_x = next_x;
	}
	next_y = player->pos_y + player->dir_y * MOVE_SPEED * direction;
	next_x = player->pos_x;
	if (map_data->map[(int)next_y][(int)next_x] == '0'
		|| map_data->map[(int)next_y][(int)next_x] == game->map_data.first_dir
		|| (map_data->map[(int)next_y][(int)next_x] == 'D' && is_door_open(game,
				render_data, (int)next_x, (int)next_y))
		|| (map_data->map[(int)next_y][(int)next_x] == 'T' && is_get_target(game,
				render_data, (int)next_x, (int)next_y)))
	{
		player->pos_y = next_y;
	}
	printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y);
	// Debugging
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
	player->dir_x = player->dir_x * cos(ROT_SPEED * direction) - player->dir_y
		* sin(ROT_SPEED * direction);
	player->dir_y = old_dir_x * sin(ROT_SPEED * direction) + player->dir_y
		* cos(ROT_SPEED * direction);
	old_plane_x = camera->plane_x;
	camera->plane_x = camera->plane_x * cos(ROT_SPEED * direction)
		- camera->plane_y * sin(ROT_SPEED * direction);
	camera->plane_y = old_plane_x * sin(ROT_SPEED * direction) + camera->plane_y
		* cos(ROT_SPEED * direction);
}

static void	close_doors(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	// printf("Player position: pos_x = %.2f, pos_y = %.2f\n", player->pos_x,
	// player->pos_y);
	// printf("Checking positions: [%d][%d+1], [%d+1][%d], [%d][%d-1],
	// [%d-1][%d]\n", (int)player->pos_x, y, x, (int)player->pos_y,
	// (int)player->pos_x, y, x, (int)player->pos_y);
	if ((x >= 0 && x < map_data->width) && (y >= 0 && y < map_data->height))
	{
		if ((map_data->map[y][(int)player->pos_x + 1] == 'D')
			|| map_data->map[(int)player->pos_y + 1][x] == 'D'
			|| (map_data->map[y][(int)player->pos_x - 1] == 'D')
			|| map_data->map[(int)player->pos_y - 1][x] == 'D')
		{
			while (i < game->door_count)
			{
				// if (game->render_data.do_sprites[i].open_door == 1)
				// {
				game->render_data.doors[i].open_door = 0;
				printf("door closed\n");
				//	break ;
				// }
				i++;
			}
		}
	}
	else
		printf("Position out of bounds: x = %d, y = %d\n", x, y);
}

static void	player_n1_sideways(t_game *game, t_map_data *map_data,
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
	if (((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == '0'
				|| map_data->map[(int)player->pos_y][(int)(player->pos_x
					+ side_dir_x * MOVE_SPEED)] == game->map_data.first_dir)
			&& (map_data->map[(int)(player->pos_y + side_dir_y
					* MOVE_SPEED)][(int)(player->pos_x)] == '0'
				|| map_data->map[(int)(player->pos_y + side_dir_y
					* MOVE_SPEED)][(int)(player->pos_x)] == game->map_data.first_dir))
		|| ((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == 'D' && is_door_open(game, render_data,
					(int)(player->pos_x + side_dir_x * MOVE_SPEED),
					(int)player->pos_y)) || (map_data->map[(int)(player->pos_y
					+ side_dir_y * MOVE_SPEED)][(int)(player->pos_x)] == 'D'
				&& is_door_open(game, render_data, (int)player->pos_x,
					(int)(player->pos_y + side_dir_y * MOVE_SPEED)))) ||
		((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == 'T' && is_get_target(game, render_data,
					(int)(player->pos_x + side_dir_x * MOVE_SPEED),
					(int)player->pos_y))) || (map_data->map[(int)(player->pos_y
				+ side_dir_y * MOVE_SPEED)][(int)(player->pos_x)] == 'T'
			&& is_get_target(game, render_data, (int)player->pos_x,
				(int)(player->pos_y + side_dir_y * MOVE_SPEED))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
	close_doors(game, map_data);
}

static void	player_n1_move(t_game *game, t_map_data *map_data,
		t_render_data *render_data, int direction)
{
	t_color		c_floor = {255, 255, 255, 255};
	t_color		c_player = {0, 0, 255, 255};
	t_player	*player;

	
	
	player = &game->render_data.player;
	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	move(game, map_data, render_data, direction);
	if (((map_data->map[(int)player->pos_y][(int)(player->pos_x + player->dir_x
					* MOVE_SPEED * direction)] == '0'
				|| map_data->map[(int)player->pos_y][(int)(player->pos_x
					+ player->dir_x * MOVE_SPEED * direction)] == game->map_data.first_dir)
			&& (map_data->map[(int)(player->pos_y + player->dir_y
					* MOVE_SPEED * direction)][(int)player->pos_x] == '0'
				|| map_data->map[(int)(player->pos_y + player->dir_y
					* MOVE_SPEED * direction)][(int)player->pos_x] == game->map_data.first_dir))
		||
		((map_data->map[(int)player->pos_y][(int)(player->pos_x + player->dir_x
					* MOVE_SPEED * direction)] == 'D' && is_door_open(game, render_data,
					(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction),
					(int)player->pos_y)) || (map_data->map[(int)(player->pos_y
					+ player->dir_y * MOVE_SPEED * direction)][(int)player->pos_x] == 'D'
				&& is_door_open(game, render_data, (int)player->pos_x,
					(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)))
			|| ((map_data->map[(int)player->pos_y][(int)(player->pos_x
						+ player->dir_x * MOVE_SPEED * direction)] == 'T'
					&& is_get_target(game, render_data, (int)(player->pos_x
							+ player->dir_x * MOVE_SPEED * direction), (int)player->pos_y))
				|| (map_data->map[(int)(player->pos_y + player->dir_y
						* MOVE_SPEED * direction)][(int)player->pos_x] == 'T'
					&& is_get_target(game, render_data, (int)player->pos_x,
						(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction))))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
	close_doors(game, map_data);
}

static void	open_doors(t_game *game, t_render_data *render_data,
		t_map_data *map_data)
{
	t_player	*player;
	double			next_x;
	double			next_y;
	int			i;

	(void)render_data;
	player = &game->render_data.player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED;
	i = 0;
	if ((map_data->map[(int)next_y][(int)player->pos_x] == 'D')
		|| map_data->map[(int)player->pos_y][(int)next_x] == 'D')
	{
		while (i < game->door_count)
		{
			if (((int)game->render_data.doors[i].pos_x == (int)next_x
				&& (int) game->render_data.doors[i].pos_y == (int)player->pos_y)
				|| ((int)player->pos_x == (int)game->render_data.doors[i].pos_x
				&& (int)next_y == game->render_data.doors[i].pos_y))
			{
				game->render_data.doors[i].open_door = 1;
				printf("door open\n");
				break ;
			}
			i++;
		}
	}
	printf("hmm the door ain't open yet. Try again!\n");
}

static void	get_target(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	printf("target x: %d y: %d \n", x, y);
	i = 0;
	if ((map_data->map[y][(int)player->pos_x] == 'T')
		|| map_data->map[(int)player->pos_y][x] == 'T')
	{
		//	render_data->sprites.open_door = 1;
		while (i < game->target_count)
		{
			if (game->render_data.targets[i].pos_x == x
				&& game->render_data.targets[i].pos_y == y)
			{
				game->render_data.targets[i].got_target = 1;
				//	game->air_caught += 1;
				//	add_look(game, game->visual_res.bubbles, WINDOW_HEIGHT / 2,
						// WINDOW_HEIGHT);
						printf("got target\n");
						break ;
			}
			i++;
		}
	}
	printf("oops you didn't get the fish. Try again!\n");
}

static void	get_air(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	printf("air x: %d y: %d \n", x, y);
	i = 0;
	if ((map_data->map[y][(int)player->pos_x] == 'L')
		|| map_data->map[(int)player->pos_y][x] == 'L')
	{
		//	render_data->sprites.open_door = 1;
		while (i < game->air_count)
		{
			if (game->render_data.air_sprites[i].pos_x == x
				&& game->render_data.air_sprites[i].pos_y == y)
			{
				game->render_data.air_sprites[i].got_air = 1;
				game->air_caught += 1;
				//	add_look(game, game->visual_res.bubbles, WINDOW_HEIGHT / 2,
						// WINDOW_HEIGHT);
						printf("got air\n");
						print_got_air(game);
						break ;
			}
			i++;
		}
	}
	printf("Hurry! You need air!\n");
}

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

	game = (t_game *)param;
	if (game->air_caught == 0)
		mlx_put_string(game->mlx_ptr, " You need air! Find the tank!", 100, 0);
	else
	{
		print_got_air(game);
	}
	render_image(game);
	// if (game->render_data.flag_hit_target == 1)
	// {
	// 	if (!is_get_target(game, &game->render_data,
	// 		game->render_data.ray.grid_pos_x, game->render_data.ray.grid_pos_y))
	// }
	calculate_sprite_position(game);
	mini_map_to_screen(game);
	if (game->air_caught != 0)
	{
		add_look(game, game->visual_res.bubbles_img, 0, WINDOW_HEIGHT
			/ 2);
		add_look(game, game->visual_res.bubbles_img, WINDOW_HEIGHT / 2,
			WINDOW_HEIGHT);
	}
}
