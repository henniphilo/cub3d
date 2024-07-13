#include "../incl/cub3d.h"

void	perform_dda(t_game *game, t_render_data *render_data, t_map_data *map_data)
{
	t_ray	*ray;

	ray = &render_data->ray;
	render_data->flag_hit_door = 0;
	render_data->flag_hit_target = 0;
	render_data->flag_hit_air = 0;
	render_data->flag_hit_wall = 0;
	(void)game;
	while (render_data->flag_hit_wall == 0)
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
		if (map_data->map[ray->grid_pos_y][ray->grid_pos_x] == '1')
			render_data->flag_hit_wall = 1;
		if (map_data->map[ray->grid_pos_y][ray->grid_pos_x] == 'D')
		{
			if (!is_door_open(game, render_data, ray->grid_pos_x, ray->grid_pos_y))
			{
				render_data->flag_hit_wall = 1;
				render_data->flag_hit_door = 1;
			}
		}
		// if (map_data->map[ray->grid_pos_x][ray->grid_pos_y] == 'T')
		// {
		// 	 if (!is_get_target(game, render_data, ray->grid_pos_x, ray->grid_pos_y))
		// 	 {
		// 		render_data->flag_hit_wall = 1;
		// 		render_data->flag_hit_target = 1;
		// 	}
		// }
		// if (map_data->map[ray->grid_pos_x][ray->grid_pos_y] == 'L')
		// {
		// 	 if (!is_get_air(game, render_data, ray->grid_pos_x, ray->grid_pos_y))
		// 	 {
		// 		render_data->flag_hit_wall = 1;
		// 		render_data->flag_hit_air = 1;
		// 	}
		// }
	}
}