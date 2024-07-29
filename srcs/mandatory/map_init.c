/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:05 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/26 11:55:00 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	direction_paths(int map_height, t_texpaths *paths,
		char **input_table)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		if (ft_strncmp(input_table[y], "NO ", 3) == 0)
		{
			paths->no = get_path(input_table[y], "NO");
		}
		if (ft_strncmp(input_table[y], "SO ", 3) == 0)
		{
			paths->so = get_path(input_table[y], "SO");
		}
		if (ft_strncmp(input_table[y], "WE ", 3) == 0)
		{
			paths->we = get_path(input_table[y], "WE");
		}
		if (ft_strncmp(input_table[y], "EA ", 3) == 0)
		{
			paths->ea = get_path(input_table[y], "EA");
		}
		y++;
	}
}

static void	color_paths(int map_height, t_texpaths *paths, char **input_table)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
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
}

void	parse_paths(int map_height, t_texpaths *paths, char **input_table)
{
	direction_paths(map_height, paths, input_table);
	color_paths(map_height, paths, input_table);
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
