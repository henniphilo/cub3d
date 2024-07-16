#include "../../incl/cub3d.h"

t_visual	init_visuals(void)
{
	t_visual	visual_res;

	visual_res.door = NULL;
	visual_res.player = NULL;
	visual_res.target = NULL;
	visual_res.air = NULL;
	visual_res.ea = NULL;
	visual_res.no = NULL;
	visual_res.so = NULL;
	visual_res.we = NULL;

	visual_res.target_img = NULL;
	return (visual_res);
}
