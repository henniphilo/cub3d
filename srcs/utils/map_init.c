#include "../../incl/cub3d.h"

void	parse_paths(int	map_height, t_texpaths *paths, char **input_table)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		if (ft_strncmp(input_table[y], "NO ", 3) == 0)
		{
			paths->NO = get_path(input_table[y], "NO");
		}
		if (ft_strncmp(input_table[y], "SO ", 3) == 0)
		{
			paths->SO = get_path(input_table[y], "SO");
		}
		if (ft_strncmp(input_table[y], "WE ", 3) == 0)
		{
			paths->WE = get_path(input_table[y], "WE");
		}
		if (ft_strncmp(input_table[y], "EA ", 3) == 0)
		{
			paths->EA = get_path(input_table[y], "EA");
		}
		if (ft_strncmp(input_table[y], "DOOR ", 5) == 0)
		{
			paths->door = get_path(input_table[y], "DOOR");
		}
		if (ft_strncmp(input_table[y], "TARGET ", 7) == 0)
		{
			paths->target = get_path(input_table[y], "TARGET");
		}
		if (ft_strncmp(input_table[y], "BUBBLES ", 8) == 0)
		{
			paths->bubbles = get_path(input_table[y], "BUBBLES");
		}
		if (ft_strncmp(input_table[y], "AIR ", 4) == 0)
		{
			paths->air = get_path(input_table[y], "AIR");
		}
		if (ft_strncmp(input_table[y], "F ", 2) == 0)
		{
			paths->floor = get_path(input_table[y], "F");
		}
		if (ft_strncmp(input_table[y], "C ", 2) == 0)
		{
			paths->ceiling = get_path(input_table[y], "C");
		}
		y++;
	}
	printf("NO: %s\n", paths->NO);
	printf("SO: %s\n", paths->SO);
	printf("WE: %s\n", paths->WE);
	printf("EA: %s\n", paths->EA);
	printf("Door: %s\n", paths->door);
	printf("Target: %s\n", paths->target);
	printf("Bubbles: %s\n", paths->bubbles);
	printf("Air: %s\n", paths->air);
}

char	*get_path(char *line, const char *direction)
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
		path = (char *)ft_calloc(len + 1, sizeof(char));
		if (!path)
			return (NULL);
		ft_strncpy(path, path_start, len);
		path[len] = '\0';
		return (path);
	}
	return (NULL);
}
