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
	space_cub(game, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	get_map(game, fd);
	if (map_input_check(game) == 1)
	{
		printf("input error \n");
		exit (1);
	}
	//printf("height %d \n width %d \n", game->map.height, game->map.width);
	close(fd);
}


int	check_map_cub(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i--;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c'
		|| file[i - 3] != '.')
	{
		return (1);
	}
	return (0);
}

char	*get_from_cub(char *line, const char *direction)
{
	char	*path;
	char	*path_start;
	char	*path_end;
	char	*dir_ptr;
	int		len;

	len = ft_strlen(line);
	dir_ptr = ft_strnstr(line, direction, len);
	if (dir_ptr != NULL)
	{
		path_start = dir_ptr + ft_strlen(direction) + 1;
		path_end = path_start;
		while (*path_start == ' ')
			path_start++;
		while (*path_end != ' ' && *path_end != '\n' && *path_end != '\0')
			path_end++;
		len = path_end - path_start;
		path = (char *)malloc(len + 1);
		if (!path)
			return (NULL);
		ft_strncpy(path, path_start, len);
		path[len] = '\0';
		return (path);
	}
	return (NULL);
}

void	cub_input(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (ft_strncmp(game->map.cub[y], "NO ", 3) == 0)
		{
			game->look.NO = get_from_cub(game->map.cub[y], "NO");
		}
		if (ft_strncmp(game->map.cub[y], "SO ", 3) == 0)
		{
			game->look.SO = get_from_cub(game->map.cub[y], "SO");
		}
		if (ft_strncmp(game->map.cub[y], "WE ", 3) == 0)
		{
			game->look.WE = get_from_cub(game->map.cub[y], "WE");
		}
		if (ft_strncmp(game->map.cub[y], "EA ", 3) == 0)
		{
			game->look.EA = get_from_cub(game->map.cub[y], "EA");
		}
		y++;
	}
	printf("NO: %s\n", game->look.NO);
	printf("SO: %s\n", game->look.SO);
	printf("WE: %s\n", game->look.WE);
	printf("EA: %s\n", game->look.EA);
}

void	which_color(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (ft_strncmp(game->map.cub[y], "F ", 2) == 0)
		{
			game->look.floor = get_from_cub(game->map.cub[y], "F");
		}
		if (ft_strncmp(game->map.cub[y], "C ", 2) == 0)
		{
			game->look.ceiling = get_from_cub(game->map.cub[y], "C");
		}
		y++;
	}
	printf("floor: %s\n", game->look.floor);
	printf("ceiling: %s\n", game->look.ceiling);
}

void	actual_map(t_game *game)
{
	int		y;
	int		map_start;
	int		is_line;
	char	*line;

	y = 0;
	map_start = 0;
	while (map_start < game->map.height)
	{
		line = game->map.cub[map_start];
		is_line = 1;
		while (line[y] != '\0')
		{
			if (line[y] != ' ' && line[y] != '1')
			{
					is_line = 0;
					break;
			}
			y++;
		}
		if (is_line)
			break ;
		map_start++;
	}
	game->map.y_axis = game->map.height - map_start;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.y_axis + 1));
	if (!game->map.map)
	{
		printf("Malloc Error in map \n");
		exit (1);
	}
	y = 0;
	while (y < game->map.y_axis)
	{
		game->map.map[y] = ft_strdup(game->map.cub[map_start + y]);
		if (!game->map.map[y])
		{
			printf("Error in dup line \n");
			exit (1);
		}
		y++;
	}
	game->map.map[game->map.y_axis] = NULL;
	printf("Map:\n");
	for (y = 0; y < game->map.y_axis; y++) {
		printf("%s", game->map.map[y]);
	}
}


int	map_input_check(t_game *game)
{
	cub_input(game);
	which_color(game);
	actual_map(game);
	free_cub(game);
	if(!game->look.EA || !game->look.NO || !game->look.SO
		|| !game->look.WE || !game->look.ceiling || !game->look.floor)
	{
		free_data(game);
		return (1);
	}
	return (0);
}

void	free_cub(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.cub[i]);
		i++;
	}
	free(game->map.cub);
}

void	free_data(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.y_axis)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	free(game->look.NO);
	free(game->look.SO);
	free(game->look.WE);
	free(game->look.EA);
	free(game->look.ceiling);
	free(game->look.floor);
}

int	walls_check(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = game->map.map;
	while (i < game->map.width)
	{
		if (map[(game->map.height) - 1][0] != '1' || map[0][i] != '1'
			|| map[game->map.height - 1][i] != '1')
			return (1);
		i++;
	}
	while (j < game->map.height)
	{
		if (map[j][0] != '1' || map[0][(game->map.width) - 1] != '1'
			|| map[j][game->map.width - 1] != '1')
			return (1);
		j++;
	}
	return (0);
}

void	space_cub(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map.cub = (char **)malloc(sizeof(char *) * (i + 1));
	game->map.height = i;
	if (!game->map.cub)
	{
		printf("Malloc Error in space cub \n");
		exit (1);
	}
}

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

void	get_map(t_game *game, int fd)
{
	char	*line_str;
	int		i;

	i = 0;
	line_str = get_next_line(fd);
	while (line_str != NULL)
	{
		if (!(line_str))
		{
			perror("Error map not readable\n");
			exit(1);
		}
		game->map.cub[i] = ft_strdup(line_str);
		if (!game->map.cub[i])
		{
			printf("Error in dup line\n");
			exit (1);
		}
		game->map.width = (ft_strlen(line_str) - 1);
		free(line_str);
		i++;
		line_str = get_next_line(fd);
	}
	printf("height %d \n width %d \n", game->map.height, game->map.width);
//	print_map(game);
	// if ((walls_check(game)) == 1)
	// {
	// 	perror("Error walls fail\n");
	// 	exit(1);
	// }
}


// tests so anpassen, dass andere werte nicht beruecksichtigt werden und in map einlesen
// dann walls check anpassen und spaces beruecksichtigen
