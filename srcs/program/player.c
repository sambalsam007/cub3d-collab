/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:45:43 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:51:14 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// draw a pixel line on the minimap, stopping at walls
void	draw_player_ray(t_cubed *cubed, t_player p, t_minimap m)
{
	float	ray_x = p.x;
	float	ray_y = p.y;
	float	step = 0.05f; // smaller = smoother
	int		map_x;
	int		map_y;
	int		minimap_x0 = m.offset_x + (int)(p.x * m.scale);
	int		minimap_y0 = m.offset_y + (int)(p.y * m.scale);
	int		minimap_x1;
	int		minimap_y1;

	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_y < 0 || map_y >= cubed->data.map_h || map_x >= cubed->data.map_w)
			break ;
		if (cubed->data.map[map_y][map_x] == '1')
			break ;

		ray_x += p.dirX * step;
		ray_y += p.dirY * step;

		minimap_x1 = m.offset_x + (int)(ray_x * m.scale);
		minimap_y1 = m.offset_y + (int)(ray_y * m.scale);

		my_mlx_pixel_put(cubed, minimap_x1, minimap_y1, 0xFF0000);
	}
}


// make player dot ~ 2x scale (so it's visible)
void	draw_player(t_cubed *cubed, t_player p, t_minimap m)
{
	int		i;
	int		j;
	int		radius;
	float	map_x;
	float	map_y;

	radius = m.scale * 2;
	i = -1;
	while (++i < radius * 2)
	{
		map_x = (float)(i - radius) / radius + p.x;
		j = -1;
		while (++j < radius * 2)
		{
			map_y = (float)(j - radius) / radius + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					m.offset_x + (int)(p.x * m.scale) \
					+ i - radius,
					m.offset_y + (int)(p.y * m.scale) \
					+ j - radius,
					p.c);
		}
	}
}

int	can_move(t_cubed *cubed, float nx, float ny)
{
	float	r;
	int		tx;
	int		ty;

	r = cubed->p.r;
	tx = (int)(nx - r);
	ty = (int)(ny - r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx + r);
	ty = (int)(ny - r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx - r);
	ty = (int)(ny + r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx + r);
	ty = (int)(ny + r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	return (1);
}

int	is_in(float x, float y, t_player p)
{
	float	dist_sqrt;
	float	dist;

	dist_sqrt = sqrtf((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	dist = dist_sqrt - p.r;
	if (dist <= 0.0f)
		return (1);
	return (0);
}

void	update_player(t_cubed *cubed)
{
	player_forward_backward(cubed);
	player_strafe_left_right(cubed);
	if (cubed->keys[KEY_J])
		player_rotate_left(cubed);
	if (cubed->keys[KEY_K])
		player_rotate_right(cubed);
}
