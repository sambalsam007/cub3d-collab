/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:20:30 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/11/06 15:20:31 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

static void	init_player_part2(t_cubed *cubed)
{
	if (cubed->data.compas == SOUTH)
	{
		cubed->p.dir_x = 0;
		cubed->p.dir_y = 1;
		cubed->p.plane_x = -0.66;
		cubed->p.plane_y = 0;
	}
	else if (cubed->data.compas == EAST)
	{
		cubed->p.dir_x = 1;
		cubed->p.dir_y = 0;
		cubed->p.plane_x = 0;
		cubed->p.plane_y = 0.66;
	}
	else if (cubed->data.compas == WEST)
	{
		cubed->p.dir_x = -1;
		cubed->p.dir_y = 0;
		cubed->p.plane_x = 0;
		cubed->p.plane_y = -0.66;
	}
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
		cubed->p.dir_x = 0;
		cubed->p.dir_y = -1;
		cubed->p.plane_x = 0.66;
		cubed->p.plane_y = 0;
	}
	else
		init_player_part2(cubed);
}
