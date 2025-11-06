/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:21:38 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/13 18:21:40 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	super_nice_loop(t_cubed *c, t_player_ray *pr, t_minimap *m, t_player *p)
{
	while (1)
	{
		pr->map_x = (int)pr->ray_x;
		pr->map_y = (int)pr->ray_y;
		if (pr->map_x < 0 || pr->map_y < 0 \
				|| pr->map_y >= c->data.map_h \
				|| pr->map_x >= c->data.map_w)
			break ;
		if (c->data.map[pr->map_y][pr->map_x] == '1')
			break ;
		pr->ray_x += p->dir_x * pr->step;
		pr->ray_y += p->dir_y * pr->step;
		pr->minimap_x1 = m->offset_x + (int)(pr->ray_x * m->scale);
		pr->minimap_y1 = m->offset_y + (int)(pr->ray_y * m->scale);
		my_mlx_pixel_put(c, pr->minimap_x1, pr->minimap_y1, 0xFF0000);
	}
}

// draw a pixel line on the minimap, stopping at walls
// pr.step => smaller = smoother
void	draw_player_ray(t_cubed *cubed, t_player p, t_minimap m)
{
	t_player_ray	pr;

	pr.ray_x = p.x;
	pr.ray_y = p.y;
	pr.step = 0.05f;
	pr.minimap_x0 = m.offset_x + (int)(p.x * m.scale);
	pr.minimap_y0 = m.offset_y + (int)(p.y * m.scale);
	super_nice_loop(cubed, &pr, &m, &p);
}
