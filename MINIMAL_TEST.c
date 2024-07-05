#include "incl/cub3d.h"

#define _WINDOW_WIDTH 800
#define _WINDOW_HEIGHT 600
#define _MAP_WIDTH 10
#define _MAP_HEIGHT 10
#define _TILE_SIZE 50
#define _MOVE_SPEED 0.1
#define _ROT_SPEED 0.05

// Define the world map
int world_map[_MAP_WIDTH][_MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Player's initial position and direction
double playerPosX = 3.0;
double playerPosY = 4.0;
double playerDirX = -1.0; // Initially facing north
double playerDirY = 0.0;
double planeX = 0.0;
double planeY = 0.66;     // 66 is the tangent of half the FOV (for a 60-degree FOV)

// Function to render the scene
void render_scene(mlx_image_t* images) {
    // Clear the images
    memset(images->pixels, 0, images->width * images->height * 4);

    // Raycasting logic
    for (int x = 0; x < images->width; x++) {
        double cameraX = 2 * x / (double)images->width - 1; // X-coordinate in camera space
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

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (playerPosX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerPosX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (playerPosY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerPosY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (world_map[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - playerPosX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - playerPosY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(images->height / perpWallDist);

        int drawStart = -lineHeight / 2 + images->height / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + images->height / 2;
        if (drawEnd >= images->height) drawEnd = images->height - 1;

        uint32_t color = 0xFF0000FF;
        if (side == 1) color = color / 2;

        for (int y = drawStart; y < drawEnd; y++) {
            images->pixels[(y * images->width + x) * 4 + 0] = (color >> 24) & 0xFF;
            images->pixels[(y * images->width + x) * 4 + 1] = (color >> 16) & 0xFF;
            images->pixels[(y * images->width + x) * 4 + 2] = (color >> 8) & 0xFF;
            images->pixels[(y * images->width + x) * 4 + 3] = color & 0xFF;
        }
    }
}

void key_hook(mlx_key_data_t keydata, void* param) {
    mlx_t* mlx = (mlx_t*)param; // Cast param to mlx_t pointer
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        if (keydata.key == MLX_KEY_W) {
            // Move forward
            if (world_map[(int)(playerPosX + playerDirX * _MOVE_SPEED)][(int)playerPosY] == 0) {
                playerPosX += playerDirX * _MOVE_SPEED;
            }
            if (world_map[(int)playerPosX][(int)(playerPosY + playerDirY * _MOVE_SPEED)] == 0) {
                playerPosY += playerDirY * _MOVE_SPEED;
            }
        }
        if (keydata.key == MLX_KEY_S) {
            // Move backward
            if (world_map[(int)(playerPosX - playerDirX * _MOVE_SPEED)][(int)playerPosY] == 0) {
                playerPosX -= playerDirX * _MOVE_SPEED;
            }
            if (world_map[(int)playerPosX][(int)(playerPosY - playerDirY * _MOVE_SPEED)] == 0) {
                playerPosY -= playerDirY * _MOVE_SPEED;
            }
        }
        if (keydata.key == MLX_KEY_A) {
            // Rotate left
            double oldDirX = playerDirX;
            playerDirX = playerDirX * cos(-_ROT_SPEED) - playerDirY * sin(-_ROT_SPEED);
            playerDirY = oldDirX * sin(-_ROT_SPEED) + playerDirY * cos(-_ROT_SPEED);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-_ROT_SPEED) - planeY * sin(-_ROT_SPEED);
            planeY = oldPlaneX * sin(-_ROT_SPEED) + planeY * cos(-_ROT_SPEED);
        }
        if (keydata.key == MLX_KEY_D) {
            // Rotate right
            double oldDirX = playerDirX;
            playerDirX = playerDirX * cos(_ROT_SPEED) - playerDirY * sin(_ROT_SPEED);
            playerDirY = oldDirX * sin(_ROT_SPEED) + playerDirY * cos(_ROT_SPEED);
            double oldPlaneX = planeX;
            planeX = planeX * cos(_ROT_SPEED) - planeY * sin(_ROT_SPEED);
            planeY = oldPlaneX * sin(_ROT_SPEED) + planeY * cos(_ROT_SPEED);
        }
        if (keydata.key == MLX_KEY_ESCAPE) {
            // Close the window
            mlx_close_window(mlx);
        }
    }
}

void loop_hook(void* param) {
    mlx_image_t* images = (mlx_image_t*)param; // Cast param to mlx_image_t pointer
    render_scene(images);
}

int main(void) {
    mlx_t* mlx = mlx_init(_WINDOW_WIDTH, _WINDOW_HEIGHT, "Raycaster", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    mlx_image_t* images = mlx_new_image(mlx, _WINDOW_WIDTH, _WINDOW_HEIGHT);
    if (!images) {
        fprintf(stderr, "Failed to create images\n");
        return EXIT_FAILURE;
    }

    mlx_image_to_window(mlx, images, 0, 0);
    mlx_key_hook(mlx, key_hook, mlx); // Pass mlx as param to key_hook
    mlx_loop_hook(mlx, loop_hook, images); // Pass images as param to loop_hook

    mlx_loop(mlx); // Enter the MLX loop, which handles rendering and events

    mlx_delete_image(mlx, images);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
