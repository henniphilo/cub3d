#include "../../incl/cub3d.h"

void	open_map(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("Error \n fd open error");
	if (check_map_cub(file) == 1)
	{
		printf("Error no .cub file\n");
		exit(0);
	}
	space_cub(game, fd); //hier hight init
	close(fd);
	fd = open(file, O_RDONLY);
	get_cub(game, fd); //hier width init
	if (map_input_check(game) == 1)
	{
		printf("input error \n");
		exit (1);
	}
	//printf("height %d \n width %d \n", game->map.height, game->map.width);
	close(fd);
}

int	get_map_start(t_game *game)
{
	int		y;
	int		map_start;
	int		is_line;
	char	*line;

	map_start = 0;
	while (map_start < game->map.height)
	{
		line = game->map.cub[map_start];
		is_line = 1;
		y = 0;
		while (line[y] != '\0')
		{
			if (line[y] != ' ' && line[y] != '1' && line[y] != '\n')
			{
					is_line = 0;
					break;
			}
			y++;
		}
		if (is_line && y > 1)
		{
			break ;
		}
		map_start++;
	}
	return (map_start);
}

void	space_map(t_game *game, int map_start)
{
	game->map.y_axis = game->map.height - map_start;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.y_axis + 1));
	game->map.x_axis = (int *)malloc(sizeof(int) * game->map.y_axis);
	if (!game->map.map || !game->map.x_axis)
	{
		printf("Malloc Error in map or x_axis\n");
		exit (1);
	}
}

void	init_map(t_game *game, int map_start)
{
	int	y;

	y = 0;
	while (y < game->map.y_axis)
	{
		game->map.map[y] = ft_strdup(game->map.cub[map_start + y]);
		game->map.x_axis[y] = ft_strlen(game->map.map[y]);
		if (!game->map.map[y])
		{
			printf("Error in dup line \n");
			exit (1);
		}
		y++;
	}
	game->map.map[game->map.y_axis] = NULL;
}

void	actual_map(t_game *game)
{
	int	map_start;

	map_start = get_map_start(game);
	space_map(game, map_start);
	init_map(game, map_start);
}
	// printf("Map:\n");
	// for (y = 0; y < game->map.y_axis; y++) {
	// 	printf("%s", game->map.map[y]);
	// }

void	print_map(t_game *game)
{
	int	x;
	int	y = 0;

	while(y < game->map.height)
	{
		x = 0;
		while(x < game->map.width)
		{
			printf("%c", game->map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
