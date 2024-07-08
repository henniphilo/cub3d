#include "../../incl/cub3d.h"


// static void	player_no_one(t_game *game, int y, int x)
// {
// 	int		pos_x;
// 	int		pos_y;
// 	t_color	c_floor = {255, 255, 255, 255};
// 	t_color	c_player = {0, 0, 255, 255};

// 	pos_x = game->map.player.pos_x;
// 	pos_y = game->map.player.pos_y;
// 	put_block(game->img, c_floor, pos_x, pos_y);
// 	if (game->map.map[pos_y + y][pos_x + x] != '1')
// 	{
// 		pos_y += y;
// 		pos_x += x;
// 	}
// 	put_block(game->img, c_player, pos_x, pos_y);
// 	game->map.player.pos_x = pos_x;
// 	game->map.player.pos_y = pos_y;
// 	printf("player direction: %c \n", game->map.player.direction);
// 	draw_dir(game, pos_x, pos_y, c_player);
// }

// char	get_direction(mlx_key_data_t key, char cur_direct)
// {
// 	if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_D)
// 	{
// 		if (cur_direct == 'N' )
// 			return ('E');
// 		if (cur_direct == 'E')
// 			return ('S');
// 		if (cur_direct == 'S')
// 			return ('W');
// 		if (cur_direct == 'W')
// 			return ('N');
// 	}
// 	else if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_A)
// 	{
// 		if (cur_direct == 'N')
// 			return ('W');
// 		if (cur_direct == 'E')
// 			return ('N');
// 		if (cur_direct == 'S')
// 			return ('E');
// 		if (cur_direct == 'W')
// 			return ('S');
// 	}
// 	else if (key.key == MLX_KEY_UP || key.key == MLX_KEY_W)
// 		return ('N');
// 	else if (key.key == MLX_KEY_DOWN || key.key == MLX_KEY_S)
// 		return ('S');
// 	return (cur_direct);
// }

// static void	end_game(t_game *game)
// {
// 	mlx_close_window(game->mlx_ptr);
// }

// static int	get_y(mlx_key_data_t key)
// {
// 	if (key.key == MLX_KEY_UP || key.key == MLX_KEY_W)
// 	{
// 		return (-1);
// 	}
// 	else if (key.key == MLX_KEY_DOWN || key.key == MLX_KEY_S)
// 	{
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// static int	get_x( mlx_key_data_t key)
// {
// 	if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_A)
// 	{
// 		return (-1);
// 	}
// 	else if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_D)
// 	{
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// void	key_hook(mlx_key_data_t key, void *ptr)
// {
// 	t_game	*game;
// 	int			x;
// 	int			y;

// 	x = 0;
// 	y = 0;
// 	game = ptr;
// 	if (key.action == MLX_RELEASE)
// 	{
// 		if (key.key == MLX_KEY_ESCAPE)
// 			end_game(game);
// 		else
// 		{
// 			y = get_y(key);
// 			x = get_x(key);
// 			game->map.player.direction = get_direction(key, game->map.player.direction);
// 		}
// 		player_no_one(game, y, x);
// 	}
// }

