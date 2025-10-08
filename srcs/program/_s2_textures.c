/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:44:30 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/08 14:44:33 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// choose which texture to use based on side + ray direction
void	define_texture_compass(t_ray *r)
{
	if (r->side == 0 && r->rayDirX > 0)
		r->texNum = WEST;
	else if (r->side == 0 && r->rayDirX < 0)
		r->texNum = EAST;
	else if (r->side == 1 && r->rayDirY > 0)
		r->texNum = NORTH;
	else if (r->side == 1 && r->rayDirY < 0)
		r->texNum = SOUTH;
}

// calculate exact hit location on the wall
void	calc_hit_position_on_wall(t_cubed *c, t_ray *r)
{
	if (r->side == 0)
		r->wallX = c->p.y + r->perpWallDist * r->rayDirY;
	else
		r->wallX = c->p.x + r->perpWallDist * r->rayDirX;
	r->wallX -= floor(r->wallX);
}
