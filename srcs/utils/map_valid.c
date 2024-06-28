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
	space_map(game, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	get_map(game, fd);
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

char	*get_path(char *line, const char *direction)
{
	char	*path;
	char	*path_start;
	char	*dir_ptr;
	int		line_len;

	line_len = ft_strlen(line);
	dir_ptr = ft_strnstr(line, direction, line_len);
	if (dir_ptr != NULL)
	{
		path_start = line + 3;
		path = ft_strdup(path_start);
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
		if (ft_stnrcmp(game->map.map[y], "NO ./", 3) == 0)
		{
			game->texture.NO = get_path(game->map.map[y], "NO");
		}
		if (ft_strncmp(game->map.map[y], "SO ./", 3) == 0)
		{
			game->texture.SO = get_path(game->map.map[y], "SO");
		}
		if (ft_strncmp(game->map.map[y], "WE ./", 3) == 0)
		{
			game->texture.WE = get_path(game->map.map[y], "WE");
		}
		if (ft_strncmp(game->map.map[y], "EA ./", 3) == 0)
		{
			game->texture.EA = get_path(game->map.map[y], "EA");
		}
		y++;
	}
	printf("NO: %s\n", game->texture.NO);
	printf("SO: %s\n", game->texture.SO);
	printf("WE: %s\n", game->texture.WE);
	printf("EA: %s\n", game->texture.EA);
}

int	map_input_check(t_game *game)
{
	if(!game->texture.EA || !game->texture.NO || !game->texture.SO
		|| !game->texture.WE)
	{
		free_data(game);
		return (1);
	}
}

void	free_data(t_game *game)
{
	free(game->texture.NO);
	free(game->texture.SO);
	free(game->texture.WE);
	free(game->texture.EA);
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


void	space_map(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!(line))
			perror("Error\n gnl problem");
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map.map = (char **)malloc(sizeof(line) * i);
	game->map.height = i;
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
		game->map.width = (ft_strlen(line_str) - 1);
		game->map.map[i] = ft_strdup(line_str);
		free(line_str);
		i++;
		line_str = get_next_line(fd);
	}
	printf("height %d \n width %d \n", game->map.height, game->map.width);
	print_map(game);
	if ((walls_check(game)) == 1)
	{
		perror("Error walls fail\n");
		exit(1);
	}
}


// tests so anpassen, dass andere werte nicht beruecksichtigt werden und in map einlesen
// dann walls check anpassen und spaces beruecksichtigen
