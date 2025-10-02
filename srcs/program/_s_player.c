#include "cubed.h"


void	_s_draw_player(t_cubed *cubed, t_player p, int scale, int offset_x, int offset_y)
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	// make player dot ~ 2x scale (so it's visible)
	int radius = scale * 2;

	i = 0;
	while (i < radius * 2)
	{
		map_x = (float)(i - radius) / radius + p.x;
		j = 0;
		while (j < radius * 2)
		{
			map_y = (float)(j - radius) / radius + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					offset_x + (int)(p.x * scale) + i - radius,
					offset_y + (int)(p.y * scale) + j - radius,
					p.c);
			j++;
		}
		i++;
	}
}

