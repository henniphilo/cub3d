#include "../../incl/cub3d.h"

// void	mm_get_textures(t_game *game)
// {
// 	game->tex.wall = mlx_load_png("./img/mm_wall.png");
// 	game->tex.player = mlx_load_png("./img/mm_player.png");
// 	game->tex.floor = mlx_load_png("./img/mm_floor.png");
// 	game->tex.target = mlx_load_png("./img/mm_target.png");
// 	if (!(game->tex.wall) || !(game->tex.player) || !(game->tex.floor)
// 		|| !(game->tex.target))
// 	{
// 		printf("Error minimap texture load\n");
// 		exit(1);
// 	}
// }

// void	mm_get_img(t_game *game)
// {
// 	mm_get_textures(game);
// 	game->img.wall = mlx_texture_to_image(game->mlx_ptr, game->tex.wall);
// 	game->img.player = mlx_texture_to_image(game->mlx_ptr, game->tex.player);
// 	game->img.floor = mlx_texture_to_image(game->mlx_ptr, game->tex.floor);
// 	game->img.target = mlx_texture_to_image(game->mlx_ptr, game->tex.target);
// 	clean_texture(game);
// }

//anstatt bilder pixel verwenden


// void	draw_mini_map(t_game *game, int x, int y)
// {
// 	if (game->map.map[y][x] == '1')
// 	{
// 		mlx_image_to_window(game->mlx_ptr, game->img.wall, (x * SSIZE),
// 			(y * SSIZE));
// 	}
// 	else if (game->map.map[y][x] == 'E')
// 	{
// 		mlx_image_to_window(game->mlx_ptr, game->img.target,
// 			(x * SSIZE), (y * SSIZE));
// 	}
// 	else if (game->map.map[y][x] == 'P')
// 	{
// 		game->map.player.pos_y = y;
// 		game->map.player.pos_x = x;
// 		mlx_image_to_window(game->mlx_ptr, game->img.player,
// 			(x * SSIZE), (y * SSIZE));
// 	}
// 	else if (game->map.map[y][x] == '0')
// 	{
// 		mlx_image_to_window(game->mlx_ptr, game->img.floor,
// 			(x * SSIZE), (y * SSIZE));
// 	}
// }

void	mini_map_init(t_game *game)
{
	int			x;
	int			y;

	game->image = mlx_new_image(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->image) {
		printf("Bild Erstellung fehlgeschlagen\n");
		return ;
	}
	y = 0;
	//mm_get_img(game);
	while (y < game->map.y_axis)
	{
		x = 0;
		while (x < game->map.x_axis[y])
		{
			draw_mini_map(game, game->image, x, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx_ptr, game->image, 0, 0);
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
	{
		color = wall;
	}
	else if (game->map.map[y][x] == 'E')
	{
		color = target;
	}
	else if (game->map.map[y][x] == 'P')
	{
		game->map.player.pos_y = y;
		game->map.player.pos_x = x;
		color = player;
	}
	else if (game->map.map[y][x] == '0')
	{
		color = floor;
	}
	else
	{
		color.r = 0;
		color.g = 0;
		color.b = 0;
		color.a = 0;
	}
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

void	put_pixel(mlx_image_t *img, int x, int y, t_color color)
{
	int		pixel_i;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	pixel_i = (y * img->width + x) * 4;
	img->pixels[pixel_i] = color.r;
	img->pixels[pixel_i + 1] = color.g;
	img->pixels[pixel_i + 2] = color.b;
	img->pixels[pixel_i + 3] = color.a;
}



// void	transparent_minimap(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	mm_size;

// 	mm_size = 5;
// 	y = 0;
// 	while (y < mm_size)
// 	{
// 			for (x = 0; x < mm_size; x++)
// 		{
// 			// Beispielkoordinaten für die Mini-Map
// 			int map_x = game->map.player.pos_x - mm_size / 2 + x;
// 			int map_y = game->map.player.pos_y - mm_size / 2 + y;

// 			// Grenzen prüfen
// 			if (map_x >= 0 && map_y >= 0 && map_x < game->map.width && map_y < game->map.height)
// 			{
// 				if (game->map.map[map_y][map_x] == '1')
// 					mlx_image_to_window(game->mlx_ptr, game->img.wall, x * SSIZE, y * SSIZE);
// 				else
// 					mlx_image_to_window(game->mlx_ptr, game->img.floor, x * SSIZE, y * SSIZE);
// 			}
// 		}
// 	}
// 	// Zeichne den Spieler auf der Mini-Map
// 	mlx_image_to_window(game->mlx_ptr, game->img.player, mm_size / 2 * SSIZE, mm_size / 2 * SSIZE);
// }
