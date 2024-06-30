#include "../../incl/cub3d.h"

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

void	get_cub(t_game *game, int fd)
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
	//print_map(game);
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
		path_start = dir_ptr + ft_strlen(direction);
		while (*path_start == ' ')
			path_start++;
		path_end = path_start;
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
