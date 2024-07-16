#include "../incl/cub3d.h"


void	player_n1_move(t_game *game, t_map_data *map_data,
		t_render_data *render_data, int direction)
{
	t_color		c_floor = {255, 255, 255, 255};
	t_color		c_player = {0, 0, 255, 255};
	t_player	*player;



	player = &game->render_data.player;
	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	move_straight(game, map_data, render_data, direction);
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
					* MOVE_SPEED * direction)] == 'D' && !is_door(game, render_data,
					(int)(player->pos_x + player->dir_x * MOVE_SPEED * direction),
					(int)player->pos_y)) || (map_data->map[(int)(player->pos_y
					+ player->dir_y * MOVE_SPEED * direction)][(int)player->pos_x] == 'D'
				&& !is_door(game, render_data, (int)player->pos_x,
					(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction)))
			|| ((map_data->map[(int)player->pos_y][(int)(player->pos_x
						+ player->dir_x * MOVE_SPEED * direction)] == 'T'
					&& !is_target(game, render_data, (int)(player->pos_x
							+ player->dir_x * MOVE_SPEED * direction), (int)player->pos_y))
				|| (map_data->map[(int)(player->pos_y + player->dir_y
						* MOVE_SPEED * direction)][(int)player->pos_x] == 'T'
					&& !is_target(game, render_data, (int)player->pos_x,
						(int)(player->pos_y + player->dir_y * MOVE_SPEED * direction))))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
	 close_doors(game, map_data);
}

void	move_straight(t_game *game, t_map_data *map_data, t_render_data *render_data,
		int direction)
{
	t_player	*player;
	double			next_x;
	double			next_y;
	t_color		c_floor = {255, 255, 255, 255};

	player = &render_data->player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED * direction;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED * direction;


	put_block_double(game->img, c_floor, player->pos_x, player->pos_y);
	if (((map_data->map[(int)player->pos_y][(int)(next_x)] == '0'
				|| map_data->map[(int)player->pos_y][(int)(next_x)] == game->map_data.first_dir)
			&& (map_data->map[(int)(next_y)][(int)player->pos_x] == '0'
				|| map_data->map[(int)(next_y)][(int)player->pos_x] == game->map_data.first_dir))
		||
		((map_data->map[(int)player->pos_y][(int)(next_x)] == 'D' && !is_door(game, render_data,
					(int)(next_x),
					(int)player->pos_y)) || (map_data->map[(int)(next_y)][(int)player->pos_x] == 'D'
				&& !is_door(game, render_data, (int)player->pos_x,
					(int)(next_y)))
			|| ((map_data->map[(int)player->pos_y][(int)(next_x)] == 'T'
					&& !is_target(game, render_data, (int)(next_x), (int)player->pos_y))
				|| (map_data->map[(int)(next_y)][(int)player->pos_x] == 'T'
					&& !is_target(game, render_data, (int)player->pos_x,
						(int)(next_y))))))

	if (map_data->map[(int)next_y][(int)next_x] == '0'
		|| map_data->map[(int)next_y][(int)next_x] == game->map_data.first_dir
		|| (map_data->map[(int)next_y][(int)next_x] == 'D' && !is_door(game,
				render_data, next_x, next_y))
		|| (map_data->map[(int)next_y][(int)next_x] == 'T' 
		&& !is_target(game, render_data, next_x, next_y)))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
		printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y);
	}
	t_color		c_player = {0, 0, 255, 255};
	put_block_double(game->img, c_player, player->pos_x, player->pos_y);
}


void	move_sideways(t_game *game, t_map_data *map_data,
		t_render_data *render_data, int direction)
{
	t_player	*player;
	double		side_dir_x;
	double		side_dir_y;
	double			next_x;
	double			next_y;

	player = &render_data->player;
	side_dir_x = (player->dir_y);
	side_dir_y = -(player->dir_x);
	next_x = player->pos_x + side_dir_x * MOVE_SPEED * direction;
	next_y = player->pos_y + side_dir_y * MOVE_SPEED * direction;
	if (map_data->map[(int)next_y][(int)next_x] == '0'
		|| map_data->map[(int)next_y][(int)next_x] == game->map_data.first_dir
		|| (map_data->map[(int)next_y][(int)next_x] == 'D' && (!(is_door(game,
				render_data, (int)next_x, (int)next_y))))
		|| (map_data->map[(int)next_y][(int)next_x] == 'T'))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
		printf("New pos_x %.2f, pos_y %.2f\n", player->pos_x, player->pos_y);
	}
}

void	player_n1_sideways(t_game *game, t_map_data *map_data,
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
	move_sideways(game, map_data, render_data, direction);
	if (((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == '0'
				|| map_data->map[(int)player->pos_y][(int)(player->pos_x
					+ side_dir_x * MOVE_SPEED)] == game->map_data.first_dir)
			&& (map_data->map[(int)(player->pos_y + side_dir_y
					* MOVE_SPEED)][(int)(player->pos_x)] == '0'
				|| map_data->map[(int)(player->pos_y + side_dir_y
					* MOVE_SPEED)][(int)(player->pos_x)] == game->map_data.first_dir))
		|| ((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == 'D' && !is_door(game, render_data,
					(int)(player->pos_x + side_dir_x * MOVE_SPEED),
					(int)player->pos_y)) || (map_data->map[(int)(player->pos_y
					+ side_dir_y * MOVE_SPEED)][(int)(player->pos_x)] == 'D'
				&& !is_door(game, render_data, (int)player->pos_x,
					(int)(player->pos_y + side_dir_y * MOVE_SPEED)))) ||
		((map_data->map[(int)player->pos_y][(int)(player->pos_x + side_dir_x
					* MOVE_SPEED)] == 'T' && !is_target(game, render_data,
					(int)(player->pos_x + side_dir_x * MOVE_SPEED),
					(int)player->pos_y))) || (map_data->map[(int)(player->pos_y
				+ side_dir_y * MOVE_SPEED)][(int)(player->pos_x)] == 'T'
			&& !is_target(game, render_data, (int)player->pos_x,
				(int)(player->pos_y + side_dir_y * MOVE_SPEED))))
		put_block_double(game->img, c_player, player->pos_x, player->pos_y);
	 close_doors(game, map_data);
}


void	rotate(t_render_data *render_data, int direction)
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

void	create_bubbles(t_game *game)
{
	if (game->render_data.count_oxy_caught != 0)
	{
		add_look(game, game->visual_res.bubbles_img, 0, WINDOW_HEIGHT
			/ 2);
		add_look(game, game->visual_res.bubbles_img, WINDOW_HEIGHT / 2,
			WINDOW_HEIGHT);
	}
}
