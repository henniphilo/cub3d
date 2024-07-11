#include "../../incl/cub3d.h"

t_game	*mini_map_init(t_game *game)
{
	fill_half(game->img, game->visual_res.c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game->img, game->visual_res.c_floor, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->img, 0, 0);
	return (game);
}

void	mini_map_to_screen(t_game *game)
{
	int		x;
	int		y;
	t_color c_player = {0, 0, 255, 255};

	y = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			draw_mini_map(game, game->img, x, y);
			x++;
		}
		y++;
	}
	put_block_double(game->img, c_player, game->render_data.player.pos_x,
		game->render_data.player.pos_y);
}

static void	init_target(t_game *game, double x, double y, int id)
{
	game->render_data.targets[id].id = id;
	game->render_data.targets[id].got_target = 0;
	game->render_data.targets[id].pos_x = x;
	game->render_data.targets[id].pos_y = y;
	game->render_data.targets[id].img = mlx_texture_to_image(game->mlx_ptr, game->visual_res.target);
}

static void	init_door(t_game *game, double x, double y, int id)
{
	game->render_data.doors[id].id = id;
	game->render_data.doors[id].open_door = 0;
	game->render_data.doors[id].pos_x = x;
	game->render_data.doors[id].pos_y = y;
	game->render_data.doors[id].img = mlx_texture_to_image(game->mlx_ptr, game->visual_res.door);
}

static void	init_count(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			if (game->map_data.map[y][x] == 'T')
			{
				game->target_count += 1;
			}
			else if (game->map_data.map[y][x] == 'D')
			{
				game->door_count += 1;
			}
			x++;
		}
		y++;
	}
	printf(" %d insgesamt targets \n", game->target_count);
	printf(" %d insgesamt doors \n", game->door_count);
}

void	init_sprites(t_game *game)
{
	int		x;
	int		y;
	int		i;
	int		j;

	printf("in init sprites\n");
	init_count(game);
	game->render_data.targets = ft_calloc(game->target_count + 1, sizeof(t_sprite));
	game->render_data.doors = ft_calloc(game->door_count + 1, sizeof(t_sprite));
	i = 0;
	j = 0;
	y = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			if (i < game->target_count && game->map_data.map[y][x] == 'T')
			{
				printf("wir haben %d targets \n", i);
				init_target(game, x, y, i);
				i += 1;
			}
			if (j < game->door_count && game->map_data.map[y][x] == 'D')
			{
				printf("wir haben %d doors \n", j);
				init_door(game, x, y, j);
				j += 1;
			}
			x++;
		}
		y++;
	}
}

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color		wall = {0,0,0,255};
	t_color		target = {255, 0, 0, 255};
	t_color		door = {0, 50, 100, 255};
	t_color		floor = {255, 255, 255, 255};
	t_color		color;

	if (game->map_data.map[y][x] == '1')
		color = wall;
	else if (game->map_data.map[y][x] == 'E')
		color = target;
	else if (game->map_data.map[y][x] == 'D')
		color = door;
	else if (game->map_data.map[y][x] == 'N' || game->map_data.map[y][x] == 'E'
		|| game->map_data.map[y][x] == 'W' || game->map_data.map[y][x] == 'S')
		color = floor;
	else if (game->map_data.map[y][x] == '0')
		color = floor;
	else
		color = game->visual_res.c_ceiling;
	put_block(img, color, x, y);
}

void	put_block(mlx_image_t *img, t_color color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i <= SSIZE)
	{
		j = 0;
		while (j <= SSIZE)
		{
			put_pixel(img, x * SSIZE + i, y * SSIZE + j, color);
			j++;
		}
		i++;
	}
}

void	put_block_double(mlx_image_t *img, t_color color, double x, double y)
{
	int	i;
	int	j;
	double	ix;
	double	iy;

	i = 0;
	ix = (x * SSIZE);
	iy = (y * SSIZE);
	//printf("Drawing block at (%.2f, %.2f) for player at (%.2f, %.2f)\n", ix, iy, x, y); // Debugging
	while (i < SSIZE)
	{
		j = 0;
		while (j < SSIZE)
		{
			put_pixel_double(img, ix + i, iy + j, color);
			j++;
		}
		i++;
	}
}

void	fill_half(mlx_image_t *img, t_color color, int start_y, int end_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < (int)img->width)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
