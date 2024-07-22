/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:21 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:17:22 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	init_input_table(t_minimap *minimap, char *file)
{
	char	*line;
	int		height;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	minimap->input_table = (char **)ft_calloc((height + 1), sizeof(char *));
	if (!minimap->input_table)
	{
		ft_putendl_fd("Error: Not enough memory to allocate an input table",
			STDERR_FILENO);
		return (-1);
	}
	minimap->height = height;
	return (0);
}

int	fill_input_table(t_minimap *minimap, char *file)
{
	char	*line_str;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	line_str = get_next_line(fd);
	while (line_str != NULL)
	{
		minimap->input_table[i] = ft_strdup(line_str);
		if (!minimap->input_table[i++])
		{
			perror("Error in dup line\n");
			return (-1);
		}
		minimap->width = (ft_strlen(line_str) - 1);
		free(line_str);
		line_str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
