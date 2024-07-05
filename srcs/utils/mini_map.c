#include "../../incl/cub3d.h"

t_game	*mini_map_init(t_game *game)
{

	t_color		c_ceiling;
	t_color		c_floor;

	game->image.c_ceiling = get_color_int(game->look.ceiling);
	game->image.c_floor = get_color_int(game->look.floor);
	c_ceiling = int_to_color(game->image.c_ceiling);
	c_floor = int_to_color(game->image.c_floor);
	fill_half(game->img, c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game->img, c_floor, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->img, 0, 0);
	return (game);
}

void	mini_map_to_screen(t_game *game)
{
	int		x;
	int		y;
	t_color c_player = {0, 0, 255, 255};

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
	put_block(game->img, c_player, (int)game->render_data.player.pos_x,
		(int)game->render_data.player.pos_y);
}

// images to images funktion bauen damit die map ueber der anderen liegen kann

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
		game->map.player.pos_y = y;
		game->map.player.pos_x = x;
		player_dir(game, x, y); // das evt wo anders initialisieren?
		color = player;
	}
	else if (game->map.map[y][x] == '0')
		color = floor;
	else
		color = int_to_color(get_color_int(game->look.ceiling));
	put_block(img, color, x, y);
}

void	draw_dir(t_game *game, int x, int y, t_color color)
{
	//int	i;
	int	dx;
	int	dy;
	int startX = x * SSIZE;
	int startY = y * SSIZE;

	//i = 0;
	dx = 0;
	dy = 0;
	printf("in draw dir\n und dir is %c \n", game->map.player.direction);
	printf("x is %d und y %d\n", x, y);
	if (game->map.player.direction == 'N')
		dy = -1;
	else if (game->map.player.direction == 'S')
		dy = 1;
	else if (game->map.player.direction == 'E')
		dx = -1;
	else if (game->map.player.direction == 'W')
		dx = 1;
	while (1)
	{
		startX += dx;
		startY += dy;
		int mapX = startX / SSIZE;
		int mapY = startY / SSIZE;

		if (mapX < 0 || mapX >= game->map.x_axis[mapY] || mapY < 0 || mapY >= game->map.y_axis
			|| game->map.map[mapY][mapX] == '1')
			break ;
		put_pixel(game->img, x * SSIZE, y * SSIZE, color);
	}
}


void	player_dir(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == 'N')
	{
		game->map.player.direction = 'N';
	}
	else if (game->map.map[y][x] == 'E')
	{
		game->map.player.direction = 'E';
	}
	else if (game->map.map[y][x] == 'S')
	{
		game->map.player.direction = 'S';
	}
	else if (game->map.map[y][x] == 'W')
	{
		game->map.player.direction = 'W';
	}
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
