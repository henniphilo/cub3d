#include "../../incl/cub3d.h"

void	mini_map_init(t_game *game)
{
	int			x;
	int			y;
	t_color		c_ceiling;
	t_color		c_floor;

	game->img = mlx_new_image(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img) {
		printf("Bild Erstellung fehlgeschlagen\n");
		return ;
	}
	game->image.c_ceiling = get_color_int(game->look.ceiling);
	game->image.c_floor = get_color_int(game->look.floor);
	c_ceiling = int_to_color(game->image.c_ceiling);
	c_floor = int_to_color(game->image.c_floor);
	fill_half(game->img, c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game->img, c_floor, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
	y = 0;
	while (y < game->map.y_axis)
	{
		x = 0;
		while (x < game->map.x_axis[y])
		{
			draw_mini_map(game, game->img, x, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx_ptr, game->img, 0, 0);
}

// image to image funktion bauen damit die map ueber der anderen liegen kann

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color		wall = {0,0,0,255};
	t_color		target = {255, 0, 0, 255};
	t_color		player = {0, 0, 255, 255};
	t_color		floor = {255, 255, 255, 255};
	t_color		color;

	if (game->map.map[y][x] == '1')
		color = wall;
	else if (game->map.map[y][x] == 'E')
		color = target;
	else if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E'
		|| game->map.map[y][x] == 'W' || game->map.map[y][x] == 'S')
	{
		player_dir(game, x, y);
		color = player;
	}
	else if (game->map.map[y][x] == '0')
		color = floor;
	else
		color = int_to_color(get_color_int(game->look.ceiling));
	put_block(img, color, x, y);
}

void	player_dir(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == 'N')
		game->map.player.direction = 'N';
	else if (game->map.map[y][x] == 'E')
		game->map.player.direction = 'E';
	else if (game->map.map[y][x] == 'S')
		game->map.player.direction = 'S';
	else if (game->map.map[y][x] == 'W')
		game->map.player.direction = 'W';
	game->map.player.pos_y = y;
	game->map.player.pos_x = x;
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
