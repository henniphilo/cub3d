#include "../../incl/cub3d.h"

t_raycast	init_raycast(void)
{
	t_raycast	raycast;

	raycast.draw_end = 0;
	raycast.draw_start = 0;
	raycast.line_height = 0;
	raycast.perp_wall_dist = 0;
	raycast.tex_pos = 0;
	raycast.tex_step_size = 0;
	raycast.tex_step_size = 0;
	raycast.tex_x = 0;
	return (raycast);
}