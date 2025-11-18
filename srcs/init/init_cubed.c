/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:51 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/11/18 11:59:46 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	init_mlx_struct(t_cubed *cubed)
{
	cubed->mlx.mlx = mlx_init();
	if (!cubed->mlx.mlx)
		return (err_msg(ERR_MLX), ERROR);
	cubed->mlx.win = mlx_new_window(cubed->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cubed->mlx.win)
		return (err_msg(ERR_WIN), ERROR);
	cubed->mlx.img = mlx_new_image(cubed->mlx.mlx, WIDTH, HEIGHT);
	if (!cubed->mlx.img)
		return (err_msg(ERR_IMG), ERROR);
	cubed->mlx.adr = mlx_get_data_addr(cubed->mlx.img, &cubed->mlx.bpp, \
		&cubed->mlx.size_line, &cubed->mlx.endian);
	return (SUCCESS);
}

static int	check_header_complete(t_cubed *cubed)
{
	t_tex	*tex;

	tex = cubed->texture;
	if (tex[NORTH].found != 1 || tex[SOUTH].found != 1 || \
		tex[WEST].found != 1 || tex[EAST].found != 1)
		return (err_msg(ERR_INV_FILE), ERROR);
	if (cubed->data.color_c == -1 || cubed->data.color_f == -1)
		return (err_msg(ERR_INV_FILE), ERROR);
	return (SUCCESS);
}

// int	check_point_around(char **lines, int i, int j)
// {
// 	if (lines[i - 1][j] == ' ' || !lines[i - 1][j])
// 		return (ERROR);	
// 	if (lines[i + 1][j] == ' ' || !lines[i + 1][j])
// 		return (ERROR);
// 	if (lines[i][j - 1] == ' ' || !lines[i][j - 1])
// 		return (ERROR);
// 	if (lines[i][j + 1] == ' ' || !lines[i][j + 1])
// 		return (ERROR);
// 	return (SUCCESS);
// }

// int	check_lines(char **lines)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (lines[++i])
// 	{
// 		j = -1;
// 		while (lines[i][++j])
// 		{
// 			if (check_point_around(lines, i, j) && (lines[i][j] == '0' || is_player(lines[i][j])))
// 				return (ERROR);
// 		}
// 	}
// 	return (SUCCESS);
// }int	check_point_around(char **lines, int i, int j)
// {
// 	if (lines[i - 1][j] == ' ' || !lines[i - 1][j])
// 		return (ERROR);	
// 	if (lines[i + 1][j] == ' ' || !lines[i + 1][j])
// 		return (ERROR);
// 	if (lines[i][j - 1] == ' ' || !lines[i][j - 1])
// 		return (ERROR);
// 	if (lines[i][j + 1] == ' ' || !lines[i][j + 1])
// 		return (ERROR);
// 	return (SUCCESS);
// }

// int	check_lines(char **lines)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (lines[++i])
// 	{
// 		j = -1;
// 		while (lines[i][++j])
// 		{
// 			if (check_point_around(lines, i, j) && (lines[i][j] == '0' || is_player(lines[i][j])))
// 				return (ERROR);
// 		}
// 	}
// 	return (SUCCESS);
// }

int	line_len(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

int	check_vertical(char **lines, int i, int j)
{
	int	len_up;
	int	len_down;

	if (i == 0)
		return (ERROR);
	len_up = line_len(lines[i - 1]);
	if (j >= len_up || lines[i - 1][j] == ' ')
		return (ERROR);
	if (!lines[i + 1])
		return (ERROR);
	len_down = line_len(lines[i + 1]);
	if (j >= len_down || lines[i + 1][j] == ' ')
		return (ERROR);
	return (SUCCESS);
}

int	check_horizontal(char **lines, int i, int j)
{
	int	len_cur;

	if (j == 0)
		return (ERROR);
	if (lines[i][j - 1] == ' ')
		return (ERROR);
	len_cur = line_len(lines[i]);
	if (j + 1 >= len_cur || lines[i][j + 1] == ' ')
		return (ERROR);
	return (SUCCESS);
}

int	check_point_around(char **lines, int i, int j)
{
	if (check_vertical(lines, i, j) == ERROR)
		return (ERROR);
	if (check_horizontal(lines, i, j) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	check_lines(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '0' || is_player(lines[i][j]))
			{
				if (check_point_around(lines, i, j) == ERROR)
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_file(t_cubed *cubed, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && lines[i][0] != '1' && lines[i][0] != ' ')
	{
		if (parse_header_line(cubed, lines[i]))
			return (err_msg(ERR_INV_MAP), ERROR);
		i++;
	}
	if (check_header_complete(cubed))
		return (ERROR);
	if (!lines[i])
		return (err_msg(ERR_INV_MAP), ERROR);
	if (check_lines(&lines[i]))
		return (err_msg(ERR_INV_MAP), ERROR);
	if (parse_map(cubed, &lines[i]))
		return (ERROR);
	return (SUCCESS);
}


static int	init_lines(char *file, char ***lines)
{
	char	*temp;

	temp = read_file(file);
	if (!temp)
		return (ERROR);
	*lines = ft_split(temp, '\n');
	free(temp);
	if (!*lines)
		return (ERROR);
	// if (check_lines(*lines))
	// 	return (ERROR);
	return (SUCCESS);
}

//init_cubed dat alles parsed zoals de map muur vloer en plafond texturen 
//	en initializeerd
//
//init Het begint door alles op Null te zetten
//init_mlx_struct Initializeren van mlx
//init_lines Leest de file en parsed het in de data struct
//parse_file Leest eerst de header en neemt de texturen uit 
//	en parsed de map erna 
//
//init_player Initializeerd de speler
int	init_cubed(t_cubed *cubed, char *file)
{
	char	**lines;

	init(cubed);
	if (init_mlx_struct(cubed))
		return (free_all(cubed), ERROR);
	if (init_lines(file, &lines))
		return (ft_freearr(lines), free_all(cubed), ERROR);
	if (parse_file(cubed, lines))
		return (ft_freearr(lines), free_all(cubed), ERROR);
	ft_freearr(lines);
	init_player(cubed);
	return (SUCCESS);
}
