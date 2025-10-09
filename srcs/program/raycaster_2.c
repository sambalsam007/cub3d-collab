/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_raycaster_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:39:12 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/08 14:39:21 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// note: the map is stored as chars, so '1' is wall (not `int 1`)
void	check_for_hit(t_cubed *c, t_ray *r)
{
	r->hit = 0;
	r->side = 0;
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= c->data.map_w \
			|| r->map_y >= c->data.map_h)
			break ;
		if (c->data.map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

void	calc_perpendicular_wall_dist(t_cubed *c, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x == 0)
			r->perp_wall_dist = (r->map_x - c->p.x + (1 - r->step_x) \
					/ 2.0) / 1e-6;
		else
			r->perp_wall_dist = (r->map_x - c->p.x + (1 - r->step_x) \
					/ 2.0) / r->ray_dir_x;
	}
	else
	{
		if (r->ray_dir_y == 0)
			r->perp_wall_dist = (r->map_y - c->p.y + (1 - r->step_y) \
					/ 2.0) / 1e-6;
		else
			r->perp_wall_dist = (r->map_y - c->p.y + (1 - r->step_y) \
					/ 2.0) / r->ray_dir_y;
	}
	if (r->perp_wall_dist < 1e-6)
		r->perp_wall_dist = 1e-6;
}

void	calc_line_height(t_ray *r)
{
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
}

void	calc_draw_start_end(t_ray *r)
{
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}
