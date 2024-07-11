#include "../../incl/cub3d.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.ray_dir_x = 0;
	ray.ray_dir_y = 0;
	ray.side_dist_x = 0;
	ray.side_dist_y = 0;
	ray.delta_dist_x = 0;
	ray.delta_dist_y = 0;
	ray.grid_pos_x = 0;
	ray.grid_pos_y = 0;
	ray.step_x = 0;
	ray.step_y = 0;
	return (ray);
}