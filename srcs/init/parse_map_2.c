/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:33:59 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/11/06 13:34:02 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	set_player(t_cubed *cubed, char c, int x, int y, int *found)
{
	if (*found == 1)
		return (err_msg(ERR_MORE_PLAYERS), ERROR);
	*found = 1;
	if (c == 'N')
		cubed->data.compas = NORTH;
	else if (c == 'E')
		cubed->data.compas = EAST;
	else if (c == 'S')
		cubed->data.compas = SOUTH;
	else if (c == 'W')
		cubed->data.compas = WEST;
	cubed->data.cords_p[0] = x;
	cubed->data.cords_p[1] = y;
	cubed->data.map[y][x] = '0';
	return (SUCCESS);
}

