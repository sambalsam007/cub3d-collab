#include "cubed.h"

// note: the map is stored as chars, so '1' is wall (not `int 1`)
void	check_for_hit(t_cubed *c, t_ray *r)
{
	r->hit = 0;
	r->side = 0;
	while (!r->hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapX < 0 || r->mapY < 0 || r->mapX >= c->data.map_w \
			|| r->mapY >= c->data.map_h)
			break ;
		if (c->data.map[r->mapY][r->mapX] == '1')
			r->hit = 1;
	}
}
