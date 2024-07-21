/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubbles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:35 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 16:22:04 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static int	random_int(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

void	add_look(t_game *game, mlx_image_t *img, int start_y, int end_y)
{
	int	rand_x;
	int	rand_y;
	int	i;
	int	num_pic;

	i = 0;
	num_pic = random_int(0, 3);
	while (i < num_pic)
	{
		// usleep(5000);
		rand_x = random_int(0, game->render_data.screen_image->width);
		rand_y = random_int(start_y, end_y
				- game->render_data.screen_image->height);
		mlx_image_to_window(game->mlx_ptr, img, rand_x, rand_y);
		// usleep(5000);
		i++;
	}
}

void	print_got_air(t_game *game)
{
	usleep(100);
	mlx_put_string(game->mlx_ptr,
		" You got air! Well done! Now catch some fish\n", 400, 0);
}
