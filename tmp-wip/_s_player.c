#include "cubed.h"

/*
void _s_draw_player(t_cubed *c) {

		printf("c (%fl)\n", c->p.fov);
		printf("c (%fl)\n", c->p.x);
		printf("c (%fl)\n", c->p.y);
		printf("c (%fl)\n", c->p.r);
		printf("c (%fl)\n", c->p.angle);
		printf("c (%d)\n", c->p.c);

		exit(0);
		return ;
}
 */

void	_s_draw_player(t_cubed *cubed, t_player p, int cell)
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	i = 0;
	while (i < cell * 2) // sample around radius area
	{
		map_x = (float)(i - cell) / cell + p.x;
		j = 0;
		while (j < cell * 2)
		{
			map_y = (float)(j - cell) / cell + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					(int)(p.x * cell) + i - cell,
					(int)(p.y * cell) + j - cell,
					p.c);
			j++;
		}
		i++;
	}
}
