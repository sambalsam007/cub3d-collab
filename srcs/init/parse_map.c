/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:14:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/19 20:25:08 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	set_player(t_cubed *cubed, char c, int x, int y, int *found)
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

static int	get_line_width(char *line)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || is_player(line[i]))
			last = i;
		i++;
	}
	return (last + 1);
}

static void	get_map_size(char **lines, int *h, int *w)
{
	int	len;

	*h = 0;
	*w = 0;
	while (lines[*h])
	{
		len = get_line_width(lines[*h]);
		if (len > *w)
			*w = len;
		(*h)++;
	}
}

static int	copy_and_find(t_cubed *cubed, char **lines, int h)
{
	int	y;
	int	found;

	y = 0;
	found = 0;
	cubed->data.map = malloc(sizeof(char *) * (h + 1));
	if (!cubed->data.map)
		return (err_msg(ERR_MAL), ERROR);
	while (y < h)
	{
		cubed->data.map[y] = ft_strdup(lines[y]);
		if (!cubed->data.map[y])
			return (err_msg(ERR_MAL), ERROR);
		for (int x = 0; cubed->data.map[y][x]; x++)
		{
			if (is_player(cubed->data.map[y][x]))
				if (set_player(cubed, cubed->data.map[y][x], x, y, &found))
					return (ERROR);
		}
		y++;
	}
	cubed->data.map[h] = NULL;
	if (found != 1)
		return (err_msg(ERR_NO_PLAYER), ERROR);
	return (SUCCESS);
}

int	parse_map(t_cubed *cubed, char **lines)
{
	int	h;
	int	w;

	get_map_size(lines, &h, &w);
	if (copy_and_find(cubed, lines, h))
		return (ft_freearr(lines), ERROR);
	if (validate_map(cubed, h, w))
		return (err_msg(ERR_INV_MAP), ERROR);
	return (SUCCESS);
}
