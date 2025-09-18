/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:14:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 18:02:43 by pdaskalo         ###   ########.fr       */
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

static int	fill_line(t_cubed *cubed, char *line, int y, int w, int *found)
{
	int	x;

	x = 0;
	while (x < w)
	{
		cubed->data.map[y][x] = ' ';
		if (line[x] && line[x] != '\n')
		{
			cubed->data.map[y][x] = line[x];
			if (is_player(line[x]))
				if (set_player(cubed, line[x], x, y, found) == ERROR)
					return (ERROR);
		}
		x++;
	}
	cubed->data.map[y][w] = '\0';
	return (SUCCESS);
}

static int	copy_and_find(t_cubed *cubed, char **lines, int h, int w)
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
		cubed->data.map[y] = malloc(w + 1);
		if (!cubed->data.map[y])
			return (err_msg(ERR_MAL), ERROR);
		if (fill_line(cubed, lines[y], y, w, &found) == ERROR)
			return (ERROR);
		y++;
	}
	cubed->data.map[h] = NULL;
	if (found != 1)
		return (err_msg(ERR_NO_PLAYER), ERROR);
	return (SUCCESS);
}

static void	get_map_size(char **lines, int *h, int *w)
{
	int	i;
	int	len;

	*h = 0;
	*w = 0;
	while (lines[*h])
	{
		i = 0;
		len = 0;
		while (lines[*h][i])
		{
			if (lines[*h][i] != '\n')
				len = i + 1;
			i++;
		}
		if (len > *w)
			*w = len;
		(*h)++;
	}
}

int	parse_map(t_cubed *cubed, char *str)
{
	char	**lines;
	int		h;
	int		w;

	lines = ft_split(str, '\n');
	if (!lines)
		return (err_msg(ERR_MAL), ERROR);
	get_map_size(lines, &h, &w);
	if (copy_and_find(cubed, lines, h, w))
		return (ft_freearr(lines), ERROR);
	ft_freearr(lines);
	if (validate_map(cubed, h, w))
		return (err_msg(ERR_INVVALID_MAP), ERROR);
	return (SUCCESS);
}
