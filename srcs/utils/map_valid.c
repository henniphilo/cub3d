#include "../../incl/cub3d.h"

void	open_map(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("Error \n fd open error");
	if (check_map_cub(file) == 1)
	{
		perror("Error \n no .cub file");
		exit(0);
	}
	space_map(game, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	get_map(game, fd);
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
		return (1);
	return (0);
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
	if ((walls_check(game)) == 1)
	{
		perror("Error walls fail\n");
		exit(1);
	}
}
