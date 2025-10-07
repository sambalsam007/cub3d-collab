#include "cubed.h"

void	calc_camera_x(t_ray *r, int current_ray_nbr)
{
	r->cameraX = 2.0 * current_ray_nbr / (double)WIDTH - 1.0;
}

void	calc_ray_dir(t_cubed *c, t_ray *r, int current_ray_nbr)
{
	r->rayDirX = c->p.dirX + c->p.planeX * r->cameraX;
	r->rayDirY = c->p.dirY + c->p.planeY * r->cameraX;
}

// x, y	= tile coordinates
// (NOT pixel coordinates)
void	set_map_xy(t_cubed *c, t_ray *r)
{
	r->mapX = (int)c->p.x;
	r->mapY = (int)c->p.y;
}

void	calc_delta_dist(t_ray *r)
{
	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1.0 / r->rayDirX);
	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1.0 / r->rayDirY);
}

void	calc_side_dist(t_cubed *c, t_ray *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (c->p.x - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - c->p.x) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (c->p.y - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - c->p.y) * r->deltaDistY;
	}
}
