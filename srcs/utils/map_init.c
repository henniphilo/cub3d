#include "../../incl/cub3d.h"

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
		if (ft_strncmp(game->map.cub[y], "DOOR ", 5) == 0)
		{
			game->look.door = get_from_cub(game->map.cub[y], "DOOR");
		}
		y++;
	}
	printf("NO: %s\n", game->look.NO);
	printf("SO: %s\n", game->look.SO);
	printf("WE: %s\n", game->look.WE);
	printf("EA: %s\n", game->look.EA);
	printf("Door: %s\n", game->look.door);
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
