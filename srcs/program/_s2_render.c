#include "../../include/cubed.h"
#define PRINT(var, fmt) \
	printf("%s ("fmt")\n", #var, var)
#define DIV \
	printf("------------------\n");

static void _s2_put_pixel(t_cubed *cubed, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) 
	    return;
    char *dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
    *(unsigned int*)dst = (unsigned int)color;
}
static void _s2_draw_vline(t_cubed *cubed, int x, int y0, int y1, int color)
{
    if (x < 0 || x >= WIDTH) 
	    return;
    if (y0 < 0) y0 = 0;
    if (y1 >= HEIGHT) y1 = HEIGHT - 1;
    for (int y = y0; y <= y1; ++y) 
	    _s2_put_pixel(cubed, x, y, color);
}

void	_s2_render_scene(t_cubed *cubed)
{


	reset_background(cubed);

	// int cubed->data.map_h = sizeof(cubed->data.map) / sizeof(cubed->data.map[0]);
	// int cubed->data.map_w = sizeof(cubed->data.map[0]) / sizeof(cubed->data.map[0][0]);

	// calc ===========
	for (int x = 0; x < WIDTH; ++x) {
	    double cameraX = 2.0 * x / (double)WIDTH - 1.0;
	    double rayDirX = cubed->p.dirX + cubed->p.planeX * cameraX;
	    double rayDirY = cubed->p.dirY + cubed->p.planeY * cameraX;

	    int mapX = (int)cubed->p.x; // tile coordinates
	    int mapY = (int)cubed->p.y;

	    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

	    int stepX = (rayDirX < 0) ? -1 : 1;
	    int stepY = (rayDirY < 0) ? -1 : 1;

	    double sideDistX;
	    double sideDistY;

		if (rayDirX < 0) {
			stepX = -1;
		sideDistX = (cubed->p.x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - cubed->p.x) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (cubed->p.y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - cubed->p.y) * deltaDistY;
		}

	    int hit = 0, side = 0;
	    while (!hit) {
		if (sideDistX < sideDistY) {
		    sideDistX += deltaDistX;
		    mapX += stepX;
		    side = 0;
		} else {
		    sideDistY += deltaDistY;
		    mapY += stepY;
		    side = 1;
		}
		if (mapX < 0 || mapY < 0 || mapX >= cubed->data.map_w || mapY >= cubed->data.map_h) 
			break;
		if (cubed->data.map[mapY][mapX] == '1') hit = 1; // must be '1', because map is stored as chars.
	    }

	    double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - cubed->p.x + (1 - stepX) / 2.0) / rayDirX;
        else
            perpWallDist = (mapY - cubed->p.y + (1 - stepY) / 2.0) / rayDirY;

        if (perpWallDist < 1e-6) perpWallDist = 1e-6;

        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        int drawEnd   = lineHeight / 2 + HEIGHT / 2;

        int color = 0x00AAFF;
        if (side == 1) color = (color >> 1) & 0x7F7F7F;

	// draw / render 3d
	_s2_draw_vline(cubed, x, drawStart, drawEnd, color);

	// draws background
	// is already being done
        // for (int y = 0; y < drawStart; ++y) 
		// _s2_put_pixel(cubed, x, y, 0x333333);
        // for (int y = drawEnd+1; y < HEIGHT; ++y) 
		// _s2_put_pixel(cubed, x, y, 0x222200);

		if (0 && (x == WIDTH/2))
		{
			system("clear");
			printf("CUB3D TILE-coordinates \n");
			DIV;
			PRINT(cameraX, "%f");
			PRINT(rayDirX, "%f");
			PRINT(rayDirY, "%f");
			PRINT(mapX, "%d");
			PRINT(mapY, "%d");
			DIV;
			PRINT(deltaDistX, "%f");
			PRINT(deltaDistY, "%f");
			PRINT(stepX, "%d");
			PRINT(stepY, "%d");
			PRINT(sideDistX, "%f");
			PRINT(sideDistY, "%f");
			DIV;
			PRINT(perpWallDist, "%f");
			DIV;
			PRINT(lineHeight, "%d");
			PRINT(drawStart, "%d");
			PRINT(drawEnd, "%d");
			// DIV;
			// PRINT(cubed->data.map_w, "%d");
			// PRINT(cubed->data.map_h, "%d");
			// PRINT(WIDTH, "%d");
			// PRINT(HEIGHT, "%d");
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
