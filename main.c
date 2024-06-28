#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int world_map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Player's initial position and direction
double playerPosX = 5.0;
double playerPosY = 5.0;
double playerDirX = -1.0; // Initially facing north
double playerDirY = 0.0;
double planeX = 0.0;
double planeY = 0.66;     // 66 is the tangent of half the FOV (for a 60-degree FOV)

void render_scene(mlx_image_t* image)
{
	uint32_t	x;

    // Clear the image
    ft_memset(image->pixels, 0, image->width * image->height * 4);

    // Raycasting logic
	x = 0;
    while (x < image->width)
    {
        double cameraX = 2 * x / (double)image->width - 1;
        double rayDirX = playerDirX + planeX * cameraX;
        double rayDirY = playerDirY + planeY * cameraX;

        int mapX = (int)playerPosX;
        int mapY = (int)playerPosY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (playerPosX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerPosX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (playerPosY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerPosY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (world_map[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - playerPosX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - playerPosY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(image->height / perpWallDist);

        int drawStart = -lineHeight / 2 + image->height / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + image->height / 2;
        if (drawEnd >= (int)image->height) drawEnd = image->height - 1;

        uint32_t color = 0xFF0000FF;
        if (side == 1) color = color / 2;

        for (int y = drawStart; y < drawEnd; y++)
        {
            image->pixels[(y * image->width + x) * 4 + 0] = (color >> 24) & 0xFF;
            image->pixels[(y * image->width + x) * 4 + 1] = (color >> 16) & 0xFF;
            image->pixels[(y * image->width + x) * 4 + 2] = (color >> 8) & 0xFF;
            image->pixels[(y * image->width + x) * 4 + 3] = color & 0xFF;
        }
		x++;
	}
}

void key_hook(mlx_key_data_t keydata, void* param) {
    mlx_t   *mlx = (mlx_t *)param;
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        if (keydata.key == MLX_KEY_W) {
            // Move forward
            if (world_map[(int)(playerPosX + playerDirX * MOVE_SPEED)][(int)playerPosY] == 0) {
                playerPosX += playerDirX * MOVE_SPEED;
            }
            if (world_map[(int)playerPosX][(int)(playerPosY + playerDirY * MOVE_SPEED)] == 0) {
                playerPosY += playerDirY * MOVE_SPEED;
            }
        }
        if (keydata.key == MLX_KEY_S) {
            // Move backward
            if (world_map[(int)(playerPosX - playerDirX * MOVE_SPEED)][(int)playerPosY] == 0) {
                playerPosX -= playerDirX * MOVE_SPEED;
            }
            if (world_map[(int)playerPosX][(int)(playerPosY - playerDirY * MOVE_SPEED)] == 0) {
                playerPosY -= playerDirY * MOVE_SPEED;
            }
        }
        if (keydata.key == MLX_KEY_D) {
            // Rotate left
            double oldDirX = playerDirX;
            playerDirX = playerDirX * cos(-ROT_SPEED) - playerDirY * sin(-ROT_SPEED);
            playerDirY = oldDirX * sin(-ROT_SPEED) + playerDirY * cos(-ROT_SPEED);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-ROT_SPEED) - planeY * sin(-ROT_SPEED);
            planeY = oldPlaneX * sin(-ROT_SPEED) + planeY * cos(-ROT_SPEED);
        }
        if (keydata.key == MLX_KEY_A) {
            // Rotate right
            double oldDirX = playerDirX;
            playerDirX = playerDirX * cos(ROT_SPEED) - playerDirY * sin(ROT_SPEED);
            playerDirY = oldDirX * sin(ROT_SPEED) + playerDirY * cos(ROT_SPEED);
            double oldPlaneX = planeX;
            planeX = planeX * cos(ROT_SPEED) - planeY * sin(ROT_SPEED);
            planeY = oldPlaneX * sin(ROT_SPEED) + planeY * cos(ROT_SPEED);
        }
        if (keydata.key == MLX_KEY_ESCAPE) {
            mlx_close_window(mlx);
        }
    }
}

void loop_hook(void* param) {
    mlx_image_t* image = (mlx_image_t*)param; // Cast param to mlx_image_t pointer
    render_scene(image);
}

int main(void) {
    mlx_t* mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    mlx_image_t* image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!image) {
        fprintf(stderr, "Failed to create image\n");
        return EXIT_FAILURE;
    }

    mlx_image_to_window(mlx, image, 0, 0);
    mlx_key_hook(mlx, key_hook, mlx); // Pass mlx as param to key_hook
    mlx_loop_hook(mlx, loop_hook, image); // Pass image as param to loop_hook

    mlx_loop(mlx); // Enter the MLX loop, which handles rendering and events

    mlx_delete_image(mlx, image);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}