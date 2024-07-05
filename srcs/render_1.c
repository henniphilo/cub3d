/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:07:31 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/05 11:17:12 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	perform_dda(t_render_data *render_data, t_map *map_data)
{
	t_ray	*ray;

	ray = &render_data->ray;
	while (render_data->flag_hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->grid_pos_x += ray->step_x;
			render_data->flag_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->grid_pos_y += ray->step_y;
			render_data->flag_side = 1;
		}
		if (map_data->map[ray->grid_pos_x][ray->grid_pos_y] > '0')
			render_data->flag_hit = 1;
	}
}

void	calculate_wall_distance_and_height(t_render_data *render_data,
		mlx_image_t *image)
{
	t_raycast	*raycast;
	t_ray		*ray;
	t_player	*player;

	player = &render_data->player;
	ray = &render_data->ray;
	raycast = &render_data->raycast;
	if (render_data->flag_side == 0)
		raycast->perp_wall_dist = (ray->grid_pos_x - player->pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		raycast->perp_wall_dist = (ray->grid_pos_y - player->pos_y + (1
					- ray->step_y) / (double)2) / ray->ray_dir_y;
	raycast->line_height = (int)(image->height / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_end >= (int)image->height)
		raycast->draw_end = image->height - 1;
}
//das verwenden fuer textures drawing
void	draw_line(int x, t_render_data *render_data, mlx_image_t *image)
{
	uint32_t	color;
	t_raycast	*raycast;
	int			y;

	raycast = &render_data->raycast;
	color = 0xFF0000FF;
	if (render_data->flag_side == 1)
		color = color / 2;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		image->pixels[(y * image->width + x) * 4 + 0] = (color >> 24) & 0xFF;
		image->pixels[(y * image->width + x) * 4 + 1] = (color >> 16) & 0xFF;
		image->pixels[(y * image->width + x) * 4 + 2] = (color >> 8) & 0xFF;
		image->pixels[(y * image->width + x) * 4 + 3] = color & 0xFF;
		y++;
	}
}

void	render_image(t_game *game)
{
	t_render_data	*render_data;
	mlx_image_t		*img;
	uint32_t		x;

	img = game->img;
	render_data = &game->render_data;
	ft_memset(img->pixels, 0, img->width * img->height * 4);
	mini_map_init(game);
	x = 0;
	while (x < img->width)
	{
		setup_render_params(x, render_data, img);
		perform_dda(render_data, &game->map);
		calculate_wall_distance_and_height(render_data, img);
		draw_line(x, render_data, img);
		x++;
	}
}
