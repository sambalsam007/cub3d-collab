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
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_num = WEST;
	else if (r->side == 0 && r->ray_dir_x < 0)
		r->tex_num = EAST;
	else if (r->side == 1 && r->ray_dir_y > 0)
		r->tex_num = NORTH;
	else if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_num = SOUTH;
}

// calculate exact hit location on the wall
void	calc_hit_position_on_wall(t_cubed *c, t_ray *r)
{
	if (r->side == 0)
		r->wall_x = c->p.y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = c->p.x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
}

// x coordinate on the texture
void	find_x_coord_on_texture(t_cubed *c, t_ray *r)
{
	r->tex_w = c->texture[r->tex_num].width;
	r->tex_h = c->texture[r->tex_num].height;
	r->tex_bpp = c->texture[r->tex_num].bpp;
	r->tex_line = c->texture[r->tex_num].size_line;
	r->tex_addr = c->texture[r->tex_num].adr;
}

// fix orientation for some sides
void	calc_tex_x(t_ray *r)
{
	r->texture_x = (int)(r->wall_x * (double)r->tex_w);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->texture_x = r->tex_w - r->texture_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->texture_x = r->tex_w - r->texture_x - 1;
	if (r->texture_x < 0)
		r->texture_x = 0;
	if (r->texture_x >= r->tex_w)
		r->texture_x = r->tex_w - 1;
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
