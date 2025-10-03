#include "../../include/cubed.h"
#define PRINT(var, fmt) \
	printf("%s ("fmt")\n", #var, var)
#define DIV \
	printf("------------------\n");

void	_s2_render_scene(t_cubed *cubed)
{


	reset_background(cubed);

	// int MAP_H = sizeof(cubed->data.map) / sizeof(cubed->data.map[0]);
	// int MAP_W = sizeof(cubed->data.map[0]) / sizeof(cubed->data.map[0][0]);

	// calc ===========
	for (int x = 0; x < WIDTH; ++x) {
	    double cameraX = 2.0 * x / (double)WIDTH - 1.0;
	    double rayDirX = cubed->p.dirX + cubed->p.planeX * cameraX;
	    double rayDirY = cubed->p.dirY + cubed->p.planeY * cameraX;

	    int mapX = (int)cubed->p.x; // tile coordinates
	    int mapY = (int)cubed->p.y;

	//     double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	//     double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

	//     int stepX = (rayDirX < 0) ? -1 : 1;
	//     int stepY = (rayDirY < 0) ? -1 : 1;

	//     double sideDistX = (rayDirX < 0) ?
	// 	(cubed->p.x - mapX) * deltaDistX :
	// 	(mapX + 1.0 - cubed->p.x) * deltaDistX;
	//     double sideDistY = (rayDirY < 0) ?
	// 	(cubed->p.y - mapY) * deltaDistY :
	// 	(mapY + 1.0 - cubed->p.y) * deltaDistY;

	//     int hit = 0, side = 0;
	//     while (!hit) {
	// 	if (sideDistX < sideDistY) {
	// 	    sideDistX += deltaDistX;
	// 	    mapX += stepX;
	// 	    side = 0;
	// 	} else {
	// 	    sideDistY += deltaDistY;
	// 	    mapY += stepY;
	// 	    side = 1;
	// 	}

	// 	if (mapX < 0 || mapY < 0 || mapX >= MAP_W || mapY >= MAP_H) break;
	// 	if (cubed->data.map[mapY][mapX] == 1) hit = 1;
	//     }

	//     double perpWallDist = (side == 0) ?
	// 	(mapX - cubed->p.x + (1 - stepX) / 2.0) / rayDirX :
	// 	(mapY - cubed->p.y + (1 - stepY) / 2.0) / rayDirY;

	//     if (perpWallDist < 1e-6) perpWallDist = 1e-6;

	//     int lineHeight = (int)(HEIGHT / perpWallDist);
	//     int drawStart = -lineHeight / 2 + HEIGHT / 2;
	//     int drawEnd   = lineHeight / 2 + HEIGHT / 2;

	//     int color = (side == 1) ? 0x555555 : 0xAAAAFF;

	//     draw_vline(&cubed->img, x, drawStart, drawEnd, color);
		if (1 && (x == WIDTH/2))
		{
		system("clear");
		printf("CUB3D TILE-coordinates \n");
		DIV;
		PRINT(cameraX, "%f");
		PRINT(rayDirX, "%f");
		PRINT(rayDirY, "%f");
		// PRINT(mapX, "%d");
		// PRINT(mapY, "%d");
		// DIV;
		// PRINT(sideDistX, "%f");
		// PRINT(sideDistY, "%f");
		// PRINT(deltaDistX, "%f");
		// PRINT(deltaDistY, "%f");
		// PRINT(perpWallDist, "%f");
		// DIV;
		// PRINT(stepX, "%d");
		// PRINT(stepY, "%d");
		// DIV;
		// PRINT(lineHeight, "%d");
		// PRINT(drawStart, "%d");
		// PRINT(drawEnd, "%d");
		DIV;
		PRINT(MAP_W, "%d");
		PRINT(MAP_H, "%d");
		PRINT(WIDTH, "%d");
		PRINT(HEIGHT, "%d");
		// PRINT(color, "%d");
		}
	}	
	// =========== calc 


	// draw to window
	_s_draw_minimap(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, \
		cubed->mlx.img, 0, 0);
}

int	_s2_render_next_frame(t_cubed *cubed)
{


	// update player
	update_player(cubed);
	int cell;
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);



	_s2_render_scene(cubed);



	return (SUCCESS);
}
