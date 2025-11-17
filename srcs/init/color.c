/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:16:32 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/11/17 13:26:20 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	validate_rgb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ',')
			return (-1);
		i++;
	}
	return (0);
}

int	parse_rgb(char *s)
{
	char	**parts;
	t_rgb	rgb[3];
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	s += i;
	if (validate_rgb(s) == -1)
		return (-1);
	parts = ft_split(s, ',');
	if (!parts)
		return (-1);
	if (ft_arrlen(parts) != 3)
		return (ft_freearr(parts), -1);
	rgb[RED] = ft_atoi(parts[0]);
	rgb[GREEN] = ft_atoi(parts[1]);
	rgb[BLUE] = ft_atoi(parts[2]);
	ft_freearr(parts);
	if (rgb[RED] < 0 || rgb[RED] > 255 || rgb[GREEN] < 0 || \
		rgb[GREEN] > 255 || rgb[BLUE] < 0 || rgb[BLUE] > 255)
		return (-1);
	return ((rgb[RED] << 16) | (rgb[GREEN] << 8) | rgb[BLUE]);
}

int	load_texture(t_cubed *cubed, t_compas dir, char *path)
{
	int		w;
	int		h;
	int		i;
	t_tex	*tex;

	i = 0;
	while (path[i] == ' ' && path[i])
		i++;
	tex = cubed->texture;
	if (tex[dir].found == 1)
		return (ERROR);
	tex[dir].img = mlx_xpm_file_to_image(cubed->mlx.mlx, path + i, &w, &h);
	if (!tex[dir].img)
		return (ERROR);
	tex[dir].adr = mlx_get_data_addr(tex[dir].img, &tex[dir].bpp, \
		&tex[dir].size_line, &tex[dir].endian);
	tex[dir].width = w;
	tex[dir].height = h;
	tex[dir].found = 1;
	return (SUCCESS);
}

static int	func(t_cubed *cubed, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (cubed->data.color_f_found == 1)
			return (ERROR);
		cubed->data.color_f = parse_rgb(line + 1);
		cubed->data.color_f_found = 1;
		return (SUCCESS);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (cubed->data.color_c_found == 1)
			return (ERROR);
		cubed->data.color_c = parse_rgb(line + 1);
		cubed->data.color_c_found = 1;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_header_line(t_cubed *cubed, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (load_texture(cubed, NORTH, &line[3]));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (load_texture(cubed, EAST, &line[3]));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (load_texture(cubed, SOUTH, &line[3]));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (load_texture(cubed, WEST, &line[3]));
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (func(cubed, line));
	if (ft_strncmp(line, "\0", 1) == 0)
		return (SUCCESS);
	return (ERROR);
}
