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
	r->ray_dir_x = c->p.dirX + c->p.planeX * camera_x;
	r->ray_dir_y = c->p.dirY + c->p.planeY * camera_x;
}

// x, y	= tile coordinates
// (NOT pixel coordinates)
void	set_map_xy(t_cubed *c, t_ray *r)
{
	r->map_x = (int)c->p.x;
	r->map_y = (int)c->p.y;
}

void	calc_delta_dist(t_ray *r)
{
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
}

void	calc_side_dist(t_cubed *c, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (c->p.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - c->p.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (c->p.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - c->p.y) * r->delta_dist_y;
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
