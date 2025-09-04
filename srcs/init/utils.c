/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:21:06 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 19:00:55 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	check_surround(char **map, int y, int x, int h, int w)
{
	int	ny;
	int	nx;

	ny = y - 1;
	nx = x;
	if (ny < 0 || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	ny = y + 1;
	if (ny >= h || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	ny = y;
	nx = x - 1;
	if (nx < 0 || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	nx = x + 1;
	if (nx >= w || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	return (SUCCESS);
}

int	validate_map(t_cubed *cubed, int h, int w)
{
	int	y;
	int	x;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			if (cubed->data.map[y][x] == '0' || is_player(cubed->data.map[y][x]))
			{
				if (check_surround(cubed->data.map, y, x, h, w) == ERROR)
					return (ERROR);
			}
		}
	}
	return (SUCCESS);
}
