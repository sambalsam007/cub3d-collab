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

int	set_player(t_cubed *cubed, char c, t_set_player sp, int *found)
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
	cubed->data.cords_p[0] = sp.x;
	cubed->data.cords_p[1] = sp.y;
	cubed->data.map[sp.y][sp.x] = '0';
	return (SUCCESS);
}
