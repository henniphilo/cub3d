#include "../../incl/cub3d.h"

t_visual	init_visuals(void)
{
	t_visual	visual_res;

	visual_res.door = NULL;
	visual_res.player = NULL;
	visual_res.target = NULL;
	visual_res.air = NULL;
	visual_res.EA = NULL;
	visual_res.NO = NULL;
	visual_res.SO = NULL;
	visual_res.WE = NULL;

	visual_res.target_img = NULL;
	return (visual_res);
}
