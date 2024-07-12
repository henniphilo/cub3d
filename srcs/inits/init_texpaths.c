#include "../../incl/cub3d.h"

t_texpaths	init_texpaths(void)
{
	t_texpaths	paths;

	paths.ceiling = NULL;
	paths.door = NULL;
	paths.target = NULL;
	paths.floor = NULL;
	paths.EA = NULL;
	paths.NO = NULL;
	paths.SO = NULL;
	paths.WE = NULL;
	paths.air = NULL;
	paths.bubbles = NULL;
	return (paths);
}