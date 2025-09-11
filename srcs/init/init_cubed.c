/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:51 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 18:03:07 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init(t_cubed *cubed)
{
	cubed->mlx.mlx = NULL;
	cubed->mlx.img = NULL;
	cubed->mlx.win = NULL;
	cubed->mlx.adr = NULL;
	cubed->data.map = NULL;
	cubed->last_time = get_time_ms();
}

void	init_player(t_cubed *cubed)
{
	cubed->p.x = cubed->data.cords_p[0] + 0.5f;
	cubed->p.y = cubed->data.cords_p[1] + 0.5f;
	cubed->p.r = 0.2f;
	cubed->p.c = 0xFF0000;
}

int	init_mlx_struct(t_cubed *cubed)
{
	cubed->mlx.mlx = mlx_init();
	if (!cubed->mlx.mlx)
		return (err_msg(ERR_MLX), ERROR);
	cubed->mlx.win = mlx_new_window(cubed->mlx.mlx, WIDTH, HEIGHT, "FdF");
	if (!cubed->mlx.win)
		return (err_msg(ERR_WIN), ERROR);
	cubed->mlx.img = mlx_new_image(cubed->mlx.mlx, WIDTH, HEIGHT);
	if (!cubed->mlx.img)
		return (err_msg(ERR_IMG), ERROR);
	cubed->mlx.adr = mlx_get_data_addr(cubed->mlx.img, &cubed->mlx.bpp, \
		&cubed->mlx.size_line, &cubed->mlx.endian);
	return (SUCCESS);
}

int	init_cubed(t_cubed *cubed, char *file)
{
	char	*temp;

	init(cubed);
	temp = read_file(file);
	if (!temp)
		return (ERROR);
	if (parse_map(cubed, temp))
		return (free_all(cubed), ERROR);
	free(temp);
	init_player(cubed);
	if (init_mlx_struct(cubed))
		return (free_all(cubed),  ERROR);
	// to be removed ones done
	printf("(%d,%d)\n", cubed->data.cords_p[1], cubed->data.cords_p[0]);
	for (int i = 0; cubed->data.map[i]; i++)
	{
		printf("%s\n", cubed->data.map[i]);
	}
	return (SUCCESS);
}