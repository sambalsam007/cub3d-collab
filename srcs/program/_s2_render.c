#include "../../include/cubed.h"

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

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3

// replace your existing _s2_render_scene with this version
void	_s2_render_scene(t_cubed *cubed)
{
	reset_background(cubed);
	t_compas texNum;

	for (int x = 0; x < WIDTH; ++x) {
	    double cameraX = 2.0 * x / (double)WIDTH - 1.0;
	    double rayDirX = cubed->p.dirX + cubed->p.planeX * cameraX;
	    double rayDirY = cubed->p.dirY + cubed->p.planeY * cameraX;

	    int mapX = (int)cubed->p.x; // tile coordinates
	    int mapY = (int)cubed->p.y;

	    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

	    double sideDistX;
	    double sideDistY;
	    int stepX, stepY;

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
		// map stored as chars: '1' is wall
		if (cubed->data.map[mapY][mapX] == '1') hit = 1;
	    }

	    double perpWallDist;
	    if (side == 0)
	        perpWallDist = (mapX - cubed->p.x + (1 - stepX) / 2.0) / (rayDirX == 0 ? 1e-6 : rayDirX);
	    else
	        perpWallDist = (mapY - cubed->p.y + (1 - stepY) / 2.0) / (rayDirY == 0 ? 1e-6 : rayDirY);
	    if (perpWallDist < 1e-6) perpWallDist = 1e-6;

	    int lineHeight = (int)(HEIGHT / perpWallDist);
	    int drawStart = -lineHeight / 2 + HEIGHT / 2;
	    int drawEnd   = lineHeight / 2 + HEIGHT / 2;
	    if (drawStart < 0) drawStart = 0;
	    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

	    /************** TEXTURE SELECTION & SAMPLING **************/
	    // choose which texture to use based on side + ray direction
	    // int texNum = 0; // 0..3 (you must define mapping in cubed.h: e.g. 0=N,1=S,2=W,3=E)
	    if (side == 0 && rayDirX > 0) texNum = WEST;
	    else if (side == 0 && rayDirX < 0) texNum = EAST;
	    else if (side == 1 && rayDirY > 0) texNum = NORTH;
	    else if (side == 1 && rayDirY < 0) texNum = SOUTH;

	    // compute exact hit location on the wall (fractional part)
	    double wallX;
	    if (side == 0)
	        wallX = cubed->p.y + perpWallDist * rayDirY;
	    else
	        wallX = cubed->p.x + perpWallDist * rayDirX;
	    wallX -= floor(wallX);

	    // x coordinate on the texture
	    int texW = cubed->texture[texNum].width;
	    int texH = cubed->texture[texNum].height;
	    int texBpp = cubed->texture[texNum].bpp;
	    int texLine = cubed->texture[texNum].size_line;
	    char *texAddr = cubed->texture[texNum].adr;

	    int texX = (int)(wallX * (double)texW);
	    // fix orientation for some sides
	    if (side == 0 && rayDirX > 0) texX = texW - texX - 1;
	    if (side == 1 && rayDirY < 0) texX = texW - texX - 1;
	    if (texX < 0) texX = 0;
	    if (texX >= texW) texX = texW - 1;

	    // how much to move in the texture for each screen pixel
	    double step = (double)texH / (double)lineHeight;
	    // starting texture y position
	    double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

	    for (int y = drawStart; y <= drawEnd; ++y) {
		int texY = (int)texPos;
		if (texY < 0) texY = 0;
		if (texY >= texH) texY = texH - 1;
		texPos += step;

		char *tex_pixel = texAddr + texY * texLine + texX * (texBpp / 8);
		int color = *(int *)tex_pixel;

		// simple shading for horizontal walls
		// if (side == 1) color = (color >> 1) & 0x7F7F7F;

		_s2_put_pixel(cubed, x, y, color);
	    }
	    /************** END TEXTURE **************/

	    // If you still want a fallback flat column (not needed when textured)
	    // int flat_color = 0x00AAFF;
	    // if (side == 1) flat_color = (flat_color >> 1) & 0x7F7F7F;
	    // _s2_draw_vline(cubed, x, drawStart, drawEnd, flat_color);

	} // end for x

	// draw to window
	_s_draw_minimap(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, cubed->mlx.img, 0, 0);
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
