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

	for (int x = 0; x < WIDTH; ++x)
	{
		t_ray r = cubed->ray;
		calc_camera_x(&r, x);
		calc_ray_dir(cubed, &r, x);
		set_map_xy(cubed, &r);
		calc_delta_dist(&r);
		calc_side_dist(cubed, &r);
		check_for_hit(cubed, &r);
		calc_perpendicular_wall_dist(cubed, &r);
		calc_line_height(&r);
		calc_draw_start_end(&r);

		// texture stuff
		define_texture_compass(&r);
		calc_hit_position_on_wall(cubed, &r);
		find_x_coord_on_texture(cubed, &r);



	    int texX = (int)(r.wallX * (double)r.texW);
	    // fix orientation for some sides
	    if (r.side == 0 && r.rayDirX > 0) texX = r.texW - texX - 1;
	    if (r.side == 1 && r.rayDirY < 0) texX = r.texW - texX - 1;
	    if (texX < 0) texX = 0;
	    if (texX >= r.texW) texX = r.texW - 1;

	    // how much to move in the texture for each screen pixel
	    double step = (double)r.texH / (double)r.lineHeight;
	    // starting texture y position
	    double texPos = (r.drawStart - HEIGHT / 2 + r.lineHeight / 2) * step;

	    for (int y = r.drawStart; y <= r.drawEnd; ++y) {
		int texY = (int)texPos;
		if (texY < 0) texY = 0;
		if (texY >= r.texH) texY = r.texH - 1;
		texPos += step;

		char *tex_pixel = r.texAddr + texY * r.texLine + texX * (r.texBpp / 8);
		int color = *(int *)tex_pixel;

		// simple shading for horizontal walls
		// if (side == 1) color = (color >> 1) & 0x7F7F7F;

		_s2_put_pixel(cubed, x, y, color);
	    }
	    /************** END TEXTURE **************/

	    // If you still want a fallback flat column (not needed when textured)
	    // int flat_color = 0x00AAFF;
	    // if (side == 1) flat_color = (flat_color >> 1) & 0x7F7F7F;
	    // _s2_draw_vline(cubed, x, r.drawStart, r.drawEnd, flat_color);

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
