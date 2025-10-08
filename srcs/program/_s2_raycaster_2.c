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

void	calc_perpendicular_wall_dist(t_cubed *c, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->rayDirX == 0)
			r->perpWallDist = (r->mapX - c->p.x + (1 - r->stepX) \
					/ 2.0) / 1e-6;
		else
			r->perpWallDist = (r->mapX - c->p.x + (1 - r->stepX) \
					/ 2.0) / r->rayDirX;
	}
	else
	{
		if (r->rayDirY == 0)
			r->perpWallDist = (r->mapY - c->p.y + (1 - r->stepY) \
					/ 2.0) / 1e-6;
		else
			r->perpWallDist = (r->mapY - c->p.y + (1 - r->stepY) \
					/ 2.0) / r->rayDirY;
	}
	if (r->perpWallDist < 1e-6)
		r->perpWallDist = 1e-6;
}
