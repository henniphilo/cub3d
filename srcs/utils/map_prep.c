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

void	init_input_table(t_map_data *map_data, int fd)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	map_data->input_table = (char **)ft_calloc((height + 1), sizeof(char *));
	if (!map_data->input_table)
	{
		printf("ft_calloc Error in init_input_table \n");
		exit (1);  // ? TODO: clean exit
	}
	map_data->height = height;
}

void	fill_input_table(t_map_data *map_data, int fd)
{
	char	*line_str;
	int		i;

	i = 0;
	line_str = get_next_line(fd);
	while (line_str != NULL)
	{
		if (!(line_str))
		{
			perror("Error map_data not readable\n");
			exit(1); // ? TODO: clean exit
		}
		map_data->input_table[i] = ft_strdup(line_str);
		if (!map_data->input_table[i])
		{
			printf("Error in dup line\n");
			exit (1);
		}
		map_data->width = (ft_strlen(line_str) - 1);
		free(line_str);
		i++;
		line_str = get_next_line(fd);
	}
}


