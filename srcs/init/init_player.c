#include "cubed.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	init_player(t_cubed *cubed)
{
	cubed->p.x = cubed->data.cords_p[0] + 0.5f;
	cubed->p.y = cubed->data.cords_p[1] + 0.5f;
	cubed->p.r = 0.2f;
	cubed->p.c = 0xFF0000;
	cubed->p.fov = M_PI / 3;
	if (cubed->data.compas == NORTH)
	{
		// cubed->p.angle = -M_PI / 2;
		cubed->p.dirX = 0;
		cubed->p.dirY = -1;
		cubed->p.planeX = 0.66;
		cubed->p.planeY = 0;
	}
	else if (cubed->data.compas == SOUTH)
	{
		// cubed->p.angle = M_PI / 2;
		cubed->p.dirX = 0;
		cubed->p.dirY = 1;
		cubed->p.planeX = -0.66;
		cubed->p.planeY = 0;
	}
	else if (cubed->data.compas == EAST)
	{
		// cubed->p.angle = 0;
		cubed->p.dirX = 1;
		cubed->p.dirY = 0;
		cubed->p.planeX = 0;
		cubed->p.planeY = 0.66;
	}
	else if (cubed->data.compas == WEST)
	{
		// cubed->p.angle = M_PI;
		cubed->p.dirX = -1;
		cubed->p.dirY = 0;
		cubed->p.planeX = 0;
		cubed->p.planeY = -0.66;
	}
}
