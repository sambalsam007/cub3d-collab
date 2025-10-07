#include "cubed.h"

/* TODO
void	first_last_ray(t_cubed *cubed, int i, int rays)
{
	if (i == 0)
	{
		cubed->minimap.first_x = cubed->ray.hit_x;
		cubed->minimap.first_y = cubed->ray.hit_y;
	}
	if (i == rays - 1)
	{
		cubed->minimap.last_x = cubed->ray.hit_x;
		cubed->minimap.last_y = cubed->ray.hit_y;
	}
}
*/

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

// # define TEX_NORTH 0
// # define TEX_SOUTH 1
// # define TEX_WEST  2
// # define TEX_EAST  3

// replace your existing _s2_render_scene with this version
void	_s2_render_scene(t_cubed *cubed)
{
	reset_background(cubed);
	t_compas texNum;

	for (int x = 0; x < WIDTH; ++x) {
		t_ray r = cubed->ray;
		calc_camera_x(&r, x);
		calc_ray_dir(cubed, &r, x);
		set_map_xy(cubed, &r);
		calc_delta_dist(&r);
		calc_side_dist(cubed, &r);




	    int hit = 0, side = 0;
	    while (!hit) {
		if (r.sideDistX < r.sideDistY) {
		    r.sideDistX += r.deltaDistX;
		    r.mapX += r.stepX;
		    side = 0;
		} else {
		    r.sideDistY += r.deltaDistY;
		    r.mapY += r.stepY;
		    side = 1;
		}
		if (r.mapX < 0 || r.mapY < 0 || r.mapX >= cubed->data.map_w || r.mapY >= cubed->data.map_h)
		    break;
		// map stored as chars: '1' is wall
		if (cubed->data.map[r.mapY][r.mapX] == '1') hit = 1;
	    }

	    double perpWallDist;
	    if (side == 0)
	        perpWallDist = (r.mapX - cubed->p.x + (1 - r.stepX) / 2.0) / (r.rayDirX == 0 ? 1e-6 : r.rayDirX);
	    else
	        perpWallDist = (r.mapY - cubed->p.y + (1 - r.stepY) / 2.0) / (r.rayDirY == 0 ? 1e-6 : r.rayDirY);
	    if (perpWallDist < 1e-6) perpWallDist = 1e-6;

	    int lineHeight = (int)(HEIGHT / perpWallDist);
	    int drawStart = -lineHeight / 2 + HEIGHT / 2;
	    int drawEnd   = lineHeight / 2 + HEIGHT / 2;
	    if (drawStart < 0) drawStart = 0;
	    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

	    /************** TEXTURE SELECTION & SAMPLING **************/
	    // choose which texture to use based on side + ray direction
	    // int texNum = 0; // 0..3 (you must define mapping in cubed.h: e.g. 0=N,1=S,2=W,3=E)
	    if (side == 0 && r.rayDirX > 0) texNum = WEST;
	    else if (side == 0 && r.rayDirX < 0) texNum = EAST;
	    else if (side == 1 && r.rayDirY > 0) texNum = NORTH;
	    else if (side == 1 && r.rayDirY < 0) texNum = SOUTH;

	    // compute exact hit location on the wall (fractional part)
	    double wallX;
	    if (side == 0)
	        wallX = cubed->p.y + perpWallDist * r.rayDirY;
	    else
	        wallX = cubed->p.x + perpWallDist * r.rayDirX;
	    wallX -= floor(wallX);

	    // x coordinate on the texture
	    int texW = cubed->texture[texNum].width;
	    int texH = cubed->texture[texNum].height;
	    int texBpp = cubed->texture[texNum].bpp;
	    int texLine = cubed->texture[texNum].size_line;
	    char *texAddr = cubed->texture[texNum].adr;

	    int texX = (int)(wallX * (double)texW);
	    // fix orientation for some sides
	    if (side == 0 && r.rayDirX > 0) texX = texW - texX - 1;
	    if (side == 1 && r.rayDirY < 0) texX = texW - texX - 1;
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
	int cell;

	update_player(cubed);
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	_s2_render_scene(cubed);
	return (SUCCESS);
}
