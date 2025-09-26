
#include "cubed.h"

#define STRIP_WIDTH 1

static void	_s_render_3d(t_cubed *cubed)
{
	int fov = cubed->p.fov;
	int num_rays = WIDTH;
	double start_angle = cubed->p.angle - (fov / 2);
	double angle_step = fov / num_rays;
	int cell;
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return ;
	int i = -1;

	// iterate over all rays
	while(++i < num_rays)
	{
		// calculate stuff
		_s_make_ray_calculations(cubed, i, angle_step, cell);


		// display info about middle ray
		if (i == (num_rays / 2))
				_s_display_ray_struct_info(cubed, i);

		for (int y = cubed->ray.wall_t; y < cubed->ray.wall_b; y++)
		    for (int x = i * STRIP_WIDTH; x < (i+1) * STRIP_WIDTH; x++)
			my_mlx_pixel_put(cubed, i, y, 0x00FF00);

			// put_pixel(&g->img, x, y, WALL_COLOR);
	}
}

int	_s_render_next_frame(t_cubed *cubed)
{
	reset_background(cubed);
	update_player(cubed);
	_s_render_3d(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, \
		cubed->mlx.img, 0, 0);
	return (SUCCESS);
}

