/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_raycaster_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:35:00 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 14:35:01 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	calc_ray_dir(t_cubed *c, t_ray *r, int current_ray_nbr)
{
	double	camera_x;

	camera_x = 2.0 * current_ray_nbr / (double)WIDTH - 1.0;
	r->rayDirX = c->p.dirX + c->p.planeX * camera_x;
	r->rayDirY = c->p.dirY + c->p.planeY * camera_x;
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

void	general_calculations(t_cubed *cubed, t_ray *ray, int current_ray_nbr)
{
	calc_ray_dir(cubed, ray, current_ray_nbr);
	set_map_xy(cubed, ray);
	calc_delta_dist(ray);
	calc_side_dist(cubed, ray);
	check_for_hit(cubed, ray);
	calc_perpendicular_wall_dist(cubed, ray);
	calc_line_height(ray);
	calc_draw_start_end(ray);
}
