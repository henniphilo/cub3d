#include "../../incl/cub3d.h"

t_camera	init_camera(void)
{
	t_camera	camera;

	camera.cameraX = 0;
	camera.plane_x = 0;
	camera.plane_y = 0;
	return (camera);
}