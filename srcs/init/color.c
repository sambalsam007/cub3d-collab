/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:16:32 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/19 20:22:03 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	parse_rgb(char *s)
{
	char	**parts;
	t_rgb	rgb[3];

	parts = ft_split(s, ',');
	if (!parts || ft_arrlen(parts) != 3)
		return (-1);
	rgb[RED] = ft_atoi(parts[0]);
	rgb[GREEN] = ft_atoi(parts[1]);
	rgb[BLUE] = ft_atoi(parts[2]);
	ft_freearr(parts);
	if (rgb[RED] < 0 || rgb[RED] > 255 || rgb[GREEN] < 0 || \
		rgb[GREEN] > 255 || rgb[BLUE] < 0 || rgb[BLUE] > 255)
		return (-1);
	return ((rgb[RED] << 16) | (rgb[GREEN] << 8) | rgb[BLUE]);
}

void	load_texture(t_cubed *cubed, t_compas dir, char *path)
{
	int		w;
	int		h;
	t_tex	*tex;

	tex = cubed->texture;
	if (tex[dir].found == 1)
	{
		printf("thing\n");
		tex[dir].found = -1;
		return ;
	}
	printf("address: %p\n", cubed->mlx.mlx);
	tex[dir].img = mlx_xpm_file_to_image(cubed->mlx.mlx, path, &w, &h);
	if (!tex[dir].img)
	{
		tex[dir].found = -1;
		return ;
	}
	tex[dir].adr = mlx_get_data_addr(tex[dir].img, &tex[dir].bpp, \
		&tex[dir].size_line, &tex[dir].endian);
	tex[dir].width = w;
	tex[dir].height = h;
	tex[dir].found = 1;
}

int parse_header_line(t_cubed *cubed, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (load_texture(cubed, NORTH, &line[3]), SUCCESS);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (load_texture(cubed, EAST, &line[3]), SUCCESS);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (load_texture(cubed, SOUTH, &line[3]), SUCCESS);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (load_texture(cubed, WEST, &line[3]), SUCCESS);
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		cubed->data.color_f = parse_rgb(line + 2);
		return (SUCCESS);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		cubed->data.color_c = parse_rgb(line + 2);
		return (SUCCESS);
	}
	if (ft_strncmp(line, "\0", 1) == 0)
		return (SUCCESS);
	return (ERROR);
}
