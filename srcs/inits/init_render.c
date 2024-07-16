#include "../../incl/cub3d.h"

t_render_data	init_render_data(void)
{
	t_render_data	render_data;

	render_data.doors = NULL;
	render_data.targets = NULL;
	render_data.flag_hit_wall = 0;
	render_data.flag_hit_door = 0;
	render_data.flag_hit_target = 0;
	render_data.flag_side = 0;
	render_data.flag_render = 1;
	render_data.camera = init_camera();
	render_data.player = init_player();
	render_data.ray = init_ray();
	render_data.raycast = init_raycast();
	render_data.count_target = 0;
	render_data.count_door = 0;
	render_data.count_oxy = 0;
	render_data.count_oxy_caught = 0;
	render_data.count_fish_caught = 0;
	return (render_data);
}
