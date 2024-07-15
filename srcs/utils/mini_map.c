#include "../../incl/cub3d.h"

t_game	*mini_map_init(t_game *game)
{
	int			i;

	i = 0;
	fill_half(game, game->visual_res.c_ceiling, 0, WINDOW_HEIGHT / 2);
	fill_half(game, game->visual_res.c_floor, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
	while (i < game->render_data.count_oxy_caught)
	{
		add_look(game, game->visual_res.bubbles_img, 0, WINDOW_HEIGHT / 2);
		add_look(game, game->visual_res.bubbles_img, WINDOW_HEIGHT / 2, WINDOW_HEIGHT);
		i++;
	}
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
	put_block_double(game->img, c_player,
		game->render_data.player.pos_x, game->render_data.player.pos_y);
	//print_got_air(game);
}

static void	init_target(t_game *game, double x, double y, int id)
{
	game->render_data.targets[id].active = 1;
	game->render_data.targets[id].pos_x = x + 0.5;
	game->render_data.targets[id].pos_y = y + 0.5;
	game->render_data.targets[id].img = mlx_texture_to_image(game->mlx_ptr, game->visual_res.target);
}

static void	init_door(t_game *game, double x, double y, int id)
{
	game->render_data.doors[id].active = 1;
	game->render_data.doors[id].pos_x = x + 0.5;
	game->render_data.doors[id].pos_y = y + 0.5;
	game->render_data.doors[id].img = mlx_texture_to_image(game->mlx_ptr, game->visual_res.door);
}

static void	init_air(t_game *game, double x, double y, int id)
{
	game->render_data.oxygen_tanks[id].active = 1;
	game->render_data.oxygen_tanks[id].pos_x = x + 0.5;
	game->render_data.oxygen_tanks[id].pos_y = y + 0.5;
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
				game->render_data.count_target += 1;
			else if (game->map_data.map[y][x] == 'D')
				game->render_data.count_door += 1;
			else if (game->map_data.map[y][x] == 'L')
				game->render_data.count_oxy += 1;
			x++;
		}
		y++;
	}
	printf(" %d insgesamt targets \n", game->render_data.count_target);
	printf(" %d insgesamt doors \n", game->render_data.count_door);
	printf(" %d insgesamt air \n", game->render_data.count_oxy);
}

void	check_sprites(t_game *game, t_render_data *render_data, int sprite_type)
{
	t_sprite	*sprite_array;
	int			sprite_count;
	int			i;

	if (sprite_type == 0) // Checking door sprites
	{
		sprite_array = render_data->doors;
		sprite_count = game->render_data.count_door;
	}
	else // Checking target sprites
	{
		sprite_array = render_data->targets;
		sprite_count = game->render_data.count_target;
	}

	i = 0;
	while (i < sprite_count)
	{
		switch (sprite_type)
		{
			case 0: // Example case for doors
				if (sprite_array[i].active)
				{
					printf("Door at (%.2f, %.2f) is closed\n", sprite_array[i].pos_x, sprite_array[i].pos_y);
				}
				else
				{
					printf("Door at (%.2f, %.2f) is open\n", sprite_array[i].pos_x, sprite_array[i].pos_y);
				}
				break;
			case 1: // Example case for targets
				if (sprite_array[i].active)
				{
					printf("Target at (%.2f, %.2f) is not acquired\n", sprite_array[i].pos_x, sprite_array[i].pos_y);
				}
				else
				{
					printf("Target at (%.2f, %.2f) is acquired\n", sprite_array[i].pos_x, sprite_array[i].pos_y);
				}
				break;
			// Add other cases as needed for different sprite types
			default:
				printf("Unknown sprite type at (%.2f, %.2f)\n", sprite_array[i].pos_x, sprite_array[i].pos_y);
				break;
		}
		i++;
	}
}

void	init_sprites(t_game *game)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		h;

	printf("in init sprites\n");
	init_count(game);
	game->render_data.targets = ft_calloc(game->render_data.count_target + 1, sizeof(t_sprite));
	game->render_data.doors = ft_calloc(game->render_data.count_door + 1, sizeof(t_sprite));
	game->render_data.oxygen_tanks = ft_calloc(game->render_data.count_oxy + 1, sizeof(t_sprite));
	i = 0;
	j = 0;
	y = 0;
	h = 0;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			if (i < game->render_data.count_target && game->map_data.map[y][x] == 'T')
			{
				init_target(game, x, y, i);
				i += 1;
			}
			if (j < game->render_data.count_door && game->map_data.map[y][x] == 'D')
			{
				init_door(game, x, y, j);
				j += 1;
			}
			if (h < game->render_data.count_oxy && game->map_data.map[y][x] == 'L')
			{
				init_air(game, x, y, h);
				h += 1;
			}
			x++;
		}
		y++;
	}
	t_render_data	*render_data = &game->render_data;
	check_sprites(game, render_data, 0);
	check_sprites(game, render_data, 1);
}

void	draw_mini_map(t_game *game, mlx_image_t *img, int x, int y)
{
	t_color		wall = {0,0,0,255};
	t_color		air = {200,0,100,255};
	t_color		target = {150, 150, 0, 255};
	t_color		door = {100, 80, 150, 255};
	t_color		floor = {255, 255, 255, 255};
	t_color		color;
	bool		should_draw;

	should_draw = true;
	if (game->map_data.map[y][x] == '1')
		color = wall;
	else if (game->map_data.map[y][x] == 'T')
	{
	//	printf("T [%d][%d] ist %d \n", x, y, is_get_target(game, &game->render_data, y, x));
		if (is_get_target(game, &game->render_data, y, x) == 1)
			color = target;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'L')
	{
	//	printf("L [%d][%d] ist %d \n", x, y, is_get_air(game, &game->render_data, y, x));
		if (is_get_air(game, &game->render_data, y, x) != 1)
			color = air;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'D')
	{
	//	printf("D [%d][%d] ist %d \n", x, y, is_door_open(game, &game->render_data, y, x));
		if (is_door_open(game, &game->render_data, y, x) == 1)
			color = door;
		else
			color = floor;
	}
	else if (game->map_data.map[y][x] == 'N' || game->map_data.map[y][x] == 'E'
		|| game->map_data.map[y][x] == 'W' || game->map_data.map[y][x] == 'S'
		|| game->map_data.map[y][x] == '0')
		color = floor;
	else
		should_draw = false;
	if (should_draw == true)
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

static void	init_bg_img(t_game *game)
{
	(void)game;
	// game->visual_res.bubbles = mlx_load_png(game->texpaths.bubbles);
	// game->visual_res.bubbles_img = mlx_texture_to_image(game->mlx_ptr, game->visual_res.bubbles);
	// mlx_delete_texture(game->tex.bubbles);
}

void	fill_half(t_game *game, t_color color, int start_y, int end_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < (int)game->img->width)
		{
			put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
	init_bg_img(game);
	//add_look(game, game->visual_res.bubbles, start_y, end_y);
}

static int	random_int(int min, int max)
{
	return (min + rand() % (max - min + 1));
}


void	add_look(t_game *game, mlx_image_t *img, int start_y, int end_y)
{
	int	rand_x;
	int	rand_y;
	// int	i;
	// int	num_pic;

	// i = 0;
	// num_pic = random_int(0, 3);
	// //printf("num pic %d \n", num_pic);
	// while (i < num_pic)
	// {
		usleep(5000);
		rand_x = random_int(0, game->img->width);
		rand_y = random_int(start_y, end_y - game->img->height);
		mlx_image_to_window(game->mlx_ptr, img, rand_x, rand_y);
		usleep(5000);
	//	i++;
	//}
}

void	print_got_air(t_game *game)
{
	// char	*fish_count;
//	mlx_image_t *img;
	// fish_count = ft_itoa(game->render_data.count_oxy_caught);
	// img = mlx_new_image(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_image_to_window(game->mlx_ptr, img, 0, 0);
	usleep(100);
	mlx_put_string(game->mlx_ptr, " You got air! Well done! Now catch some fish\n", 100, 0);
	//mlx_put_string(game->mlx_ptr, fish_count, 5, 5);
	//free(fish_count);
//	ft_printf("got %d of air %d\n", game->render_data.count_oxy_caught, game->render_data.count_oxy);
}
