/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_textures_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:44:30 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 13:51:36 by samd-hoo         ###   ########.fr       */
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

// x coordinate on the texture
void	find_x_coord_on_texture(t_cubed *c, t_ray *r)
{
	r->texW = c->texture[r->texNum].width;
	r->texH = c->texture[r->texNum].height;
	r->texBpp = c->texture[r->texNum].bpp;
	r->texLine = c->texture[r->texNum].size_line;
	r->texAddr = c->texture[r->texNum].adr;
}

// fix orientation for some sides
void	calc_tex_x(t_ray *r)
{
	r->texX = (int)(r->wallX * (double)r->texW);
	if (r->side == 0 && r->rayDirX > 0)
		r->texX = r->texW - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->texX = r->texW - r->texX - 1;
	if (r->texX < 0)
		r->texX = 0;
	if (r->texX >= r->texW)
		r->texX = r->texW - 1;
}

void	texture_calculations(t_cubed *cubed, t_ray *ray, int current_ray_nbr)
{
	define_texture_compass(ray);
	calc_hit_position_on_wall(cubed, ray);
	find_x_coord_on_texture(cubed, ray);
	calc_tex_x(ray);
	calc_step(ray);
	calc_tex_pos(ray);
	draw_vertical_column(cubed, ray, current_ray_nbr);
}
