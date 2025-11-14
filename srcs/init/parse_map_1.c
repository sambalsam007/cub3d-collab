/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:14:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/10/31 16:41:33 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_line_width(char *line)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (line[i])
	{
		// todo != 1, 0, !isplayer, ! ' ' ! '\t'
		if (line[i] == '1' || line[i] == '0' || is_player(line[i]))
			last = i;
		i++;
	}
	return (last + 1);
}

static void	set_map_size(t_cubed *cubed, char **lines, int *h, int *w)
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
	cubed->data.map_h = *h;
	cubed->data.map_w = *w;
}

static int	check_line_player(t_cubed *cubed, char *line, int y, int *found)
{
	t_set_player	sp;

	sp.x = 0;
	sp.y = y;
	while (line[sp.x])
	{
		if (is_player(line[sp.x]))
			if (set_player(cubed, line[sp.x], sp, found))
				return (ERROR);
		sp.x++;
	}
	return (SUCCESS);
}

static int	copy_and_find(t_cubed *cubed, char **lines, int h)
{
	int	y;
	int	found;
	int	i;

	y = 0;
	i = 0;
	found = 0;
	cubed->data.map = malloc(sizeof(char *) * (h + 1));
	if (!cubed->data.map)
		return (err_msg(ERR_MAL), ERROR);
	while (i <= h)
		cubed->data.map[i++] = NULL;
	while (y < h)
	{
		cubed->data.map[y] = ft_strdup(lines[y]);
		if (!cubed->data.map[y])
			return (err_msg(ERR_MAL), ERROR);
		if (check_line_player(cubed, cubed->data.map[y], y, &found))
			return (ERROR);
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

	set_map_size(cubed, lines, &h, &w);
	if (copy_and_find(cubed, lines, h))
		return (ERROR);
	if (validate_map(cubed, h, w))
		return (err_msg(ERR_INV_MAP), ERROR);
	return (SUCCESS);
}

/*
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
*/
