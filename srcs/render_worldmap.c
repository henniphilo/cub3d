/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_worldmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:07:31 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/14 21:26:12 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void calculate_initial_side_distances(t_render_data* render_data) {
	t_ray		*ray;
	t_player	*player;

	ray = &render_data->ray;
	player = &render_data->player;
	if (ray->ray_dir_x < 0) {
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->grid_pos_x) * ray->delta_dist_x;
	} else {
		ray->step_x = 1;
		ray->side_dist_x = (ray->grid_pos_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}

	if (ray->ray_dir_y < 0) {
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->grid_pos_y) * ray->delta_dist_y;
	} else {
		ray->step_y = 1;
		ray->side_dist_y = (ray->grid_pos_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void	setup_render_params(uint32_t x, t_render_data *render_data, mlx_image_t* image)
{
	t_ray		*ray;
	t_camera	*camera;
	t_player	*player;

	ray = &render_data->ray;
	camera = &render_data->camera;
	player = &render_data->player;
	camera->cameraX = 2 * x / (double)image->width - 1;
	ray->ray_dir_x = player->dir_x + camera->plane_x * camera->cameraX;
	ray->ray_dir_y = player->dir_y + camera->plane_y * camera->cameraX;
	ray->grid_pos_x = (int)player->pos_x;
	ray->grid_pos_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	render_data->flag_hit_wall = 0;
	calculate_initial_side_distances(render_data);
}

void	calculate_wall_distance_and_height(int x, t_render_data *render_data,
		mlx_image_t *image, mlx_texture_t *tex)
{
	t_raycast	*raycast;
	t_ray		*ray;
	t_player	*player;
	double		wall_x;

	player = &render_data->player;
	ray = &render_data->ray;
	raycast = &render_data->raycast;
	if (render_data->flag_side == 0)
		raycast->perp_wall_dist = (ray->grid_pos_x - player->pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		raycast->perp_wall_dist = (ray->grid_pos_y - player->pos_y + (1
					- ray->step_y) / (double)2) / ray->ray_dir_y;
	render_data->z_buffer[x] = raycast->perp_wall_dist;
	raycast->line_height = (int)(image->height / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + image->height / 2;
	if (raycast->draw_end >= (int)image->height)
		raycast->draw_end = image->height - 1;

	if (render_data->flag_side == 0)
		wall_x = player->pos_y + raycast->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->pos_x + raycast->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);


	render_data->raycast.tex_x = (int)(wall_x * (double)tex->width); //% tex->width;
	if (render_data->flag_side == 0 && ray->ray_dir_x > 0)
		render_data->raycast.tex_x = tex->width - render_data->raycast.tex_x - 1;
	if (render_data->flag_side == 1 && ray->ray_dir_y < 0)
		render_data->raycast.tex_x = tex->width - render_data->raycast.tex_x - 1;

	render_data->raycast.tex_step_size = 1.0 * tex->height / render_data->raycast.line_height;
	render_data->raycast.tex_pos = (render_data->raycast.draw_start - image->height / 2 + render_data->raycast.line_height / 2) * render_data->raycast.tex_step_size;
}

void	render_worldmap(t_game *game)
{
	t_render_data	*render_data;
	mlx_image_t		*img;
	uint32_t		x;
	mlx_texture_t	*selected_texture;

	img = game->img;
	render_data = &game->render_data;
	ft_memset(img->pixels, 0, img->width * img->height * 4);
	mini_map_init(game);

	x = 0;
	while (x < img->width)
	{
		setup_render_params(x, render_data, img);
		perform_dda(game, render_data, &game->map_data);
		selected_texture = NULL;

		if (render_data->flag_side == 0)
		{
			if (render_data->ray.ray_dir_x > 0)
				selected_texture = game->visual_res.EA;
			else
				selected_texture = game->visual_res.WE;
		}
		else
		{
			if (render_data->ray.ray_dir_y > 0)
				selected_texture = game->visual_res.SO;
			else
				selected_texture = game->visual_res.NO;
		}
		if (selected_texture != NULL)
		{
			calculate_wall_distance_and_height(x, render_data, img, selected_texture);
			draw_line(x, render_data, img, selected_texture);
		}

		if (render_data->flag_hit_door == 1)
		{
			if (is_door_open(game, render_data, render_data->ray.grid_pos_x, render_data->ray.grid_pos_y))
			{
				//ueberprueft was falsches
				selected_texture = game->visual_res.door;
				calculate_wall_distance_and_height(x, render_data, img, selected_texture);
				draw_line(x, render_data, img, selected_texture);
			}
		}
		// if (render_data->flag_hit_air == 1)
		// {
		// 	if (!is_get_air(game, render_data, render_data->ray.grid_pos_x, render_data->ray.grid_pos_y))
		// 	{
		// 		selected_texture = game->visual_res.air;
		// 		calculate_wall_distance_and_height(x, render_data, img, selected_texture);
		// 		draw_line(x, render_data, img, selected_texture);
		// 	}
		// }

		x++;
	}
	// clean_texture(game); // eventuell doch ?
}

