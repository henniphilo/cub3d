#include "../../incl/cub3d.h"

void	mm_get_textures(t_game *game)
{
	game->tex.wall = mlx_load_png("./img/mm_wall.png");
	game->tex.player = mlx_load_png("./img/mm_player.png");
	game->tex.floor = mlx_load_png("./img/mm_floor.png");
	game->tex.target = mlx_load_png("./img/mm_target.png");
	if (!(game->tex.wall) || !(game->tex.player) || !(game->tex.floor)
		|| !(game->tex.target))
	{
		printf("Error minimap texture load\n");
		exit(1);
	}
}

void	mm_get_img(t_game *game)
{
	mm_get_textures(game);
	game->img.wall = mlx_texture_to_image(game->mlx_ptr, game->tex.wall);
	game->img.player = mlx_texture_to_image(game->mlx_ptr, game->tex.player);
	game->img.floor = mlx_texture_to_image(game->mlx_ptr, game->tex.floor);
	game->img.target = mlx_texture_to_image(game->mlx_ptr, game->tex.target);
	clean_texture(game);
}

void	draw_mini_map(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == '1')
	{
		mlx_image_to_window(game->mlx_ptr, game->img.wall, (x * SSIZE),
			(y * SSIZE));
	}
	else if (game->map.map[y][x] == 'E')
	{
		mlx_image_to_window(game->mlx_ptr, game->img.target,
			(x * SSIZE), (y * SSIZE));
	}
	else if (game->map.map[y][x] == 'P')
	{
		game->map.player.pos_y = y;
		game->map.player.pos_x = x;
		mlx_image_to_window(game->mlx_ptr, game->img.player,
			(x * SSIZE), (y * SSIZE));
	}
	else if (game->map.map[y][x] == '0')
	{
		mlx_image_to_window(game->mlx_ptr, game->img.floor,
			(x * SSIZE), (y * SSIZE));
	}
}

void	mini_map_init(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	//mm_get_img(game);
	while (y < game->map.y_axis)
	{
		x = 0;
		while (x < game->map.x_axis[y])
		{
			draw_mini_map(game, x, y);
			x++;
		}
		y++;
	}
}

void	transparent_minimap(t_game *game)
{
	int	x;
	int	y;
	int	mm_size;

	mm_size = 5;
	y = 0;
	while (y < mm_size)
	{
			for (x = 0; x < mm_size; x++)
		{
			// Beispielkoordinaten für die Mini-Map
			int map_x = game->map.player.pos_x - mm_size / 2 + x;
			int map_y = game->map.player.pos_y - mm_size / 2 + y;

			// Grenzen prüfen
			if (map_x >= 0 && map_y >= 0 && map_x < game->map.width && map_y < game->map.height)
			{
				if (game->map.map[map_y][map_x] == '1')
					mlx_image_to_window(game->mlx_ptr, game->img.wall, x * SSIZE, y * SSIZE);
				else
					mlx_image_to_window(game->mlx_ptr, game->img.floor, x * SSIZE, y * SSIZE);
			}
		}
	}
	// Zeichne den Spieler auf der Mini-Map
	mlx_image_to_window(game->mlx_ptr, game->img.player, mm_size / 2 * SSIZE, mm_size / 2 * SSIZE);
}
