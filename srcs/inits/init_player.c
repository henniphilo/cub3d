#include "../../incl/cub3d.h"

t_player	init_player(void)
{
	t_player	player;

	player.dir_x = 0;
	player.dir_y = 0;
	player.pos_x = 0;
	player.pos_y = 0;
	player.prev_pos_x = 0;
	player.prev_pos_y = 0;
	return (player);
}