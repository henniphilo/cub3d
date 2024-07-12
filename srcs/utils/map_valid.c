#include "../../incl/cub3d.h"

void	open_map(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("Error \n fd open error");
	if (check_file_ending_cub(file) == 1)
	{
		printf("Error no .cub file\n");
		exit(0);
	}
	init_input_table(&game->map_data, fd); // hier hight init
	close(fd);
	fd = open(file, O_RDONLY);
	fill_input_table(&game->map_data, fd); // hier width init
	if (parse_input_table(game) == 1)
		// hier drin wird actual map_data erstellt
	{
		printf("input error \n");
		exit(1);
	}
	// printf("height %d \n width %d \n", game->map_data.height,
		// game->map_data.width);
	close(fd);
}

int	get_map_start(unsigned int map_height, char **input_table)
{
	int				y;
	unsigned int	map_start;
	int				is_line;
	char			*line;

	map_start = 0;
	while (map_start < map_height)
	{
		line = input_table[map_start];
		is_line = 1;
		y = 0;
		while (line[y] != '\0')
		{
			if (line[y] != ' ' && line[y] != '1' && line[y] != '\n')
			{
				is_line = 0;
				break ;
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

void	init_map(t_map_data *map_data, int map_start)
{
	map_data->y_axis = map_data->height - map_start;
	map_data->map = (char **)ft_calloc((map_data->y_axis + 1), sizeof(char *));
	map_data->x_axis = (int *)ft_calloc(map_data->y_axis, sizeof(int));
	if (!map_data->map || !map_data->x_axis)
	{
		printf("ft_calloc Error in map or x_axis\n");
		exit(1); // TODO: Clean exit
	}
}

void	create_map(t_map_data *map_data)
{
	int	y;
	int	map_start;

	y = 0;
	map_start = get_map_start(map_data->height, map_data->input_table);
	init_map(map_data, map_start);
	while (y < map_data->y_axis)
	{
		map_data->map[y] = ft_strdup(map_data->input_table[map_start + y]);
		if (!map_data->map[y])
		{
			printf("Error in dup line \n");
			exit(1); // ? TODO: clean exit
		}
		map_data->x_axis[y] = ft_strlen(map_data->map[y]);
		y++;
	}
	map_data->map[map_data->y_axis] = NULL;
}

void	print_map(t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			printf("%c", map_data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
