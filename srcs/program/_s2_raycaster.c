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
