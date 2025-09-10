/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:51 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 19:35:17 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init(t_cubed *cubed)
{
	cubed->mlx.mlx = NULL;
	cubed->mlx.image = NULL;
	cubed->mlx.win = NULL;
	cubed->data.map = NULL;
}

int	init_cubed(t_cubed *cubed, char *file)
{
	char	*temp;

	init(cubed);
	temp = read_file(file);
	if (!temp)
		return (ERROR);
	if (parse_map(cubed, temp))
		return (ERROR);
	free(temp);
	printf("(%d,%d)\n", cubed->data.cords_p[1], cubed->data.cords_p[0]);
	for (int i = 0; cubed->data.map[i]; i++)
	{
		printf("%s\n", cubed->data.map[i]);
	}
	return (SUCCESS);
}
