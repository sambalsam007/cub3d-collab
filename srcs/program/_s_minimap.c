#include "cubed.h"

void	_s_my_mlx_pixel_put(t_cubed *cubed, int x, int y, int color)
{
	char	*dst;

	dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

void	_s_draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			_s_my_mlx_pixel_put(cubed, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	_s_draw_minimap(t_cubed *cubed)
{
	int	x;
	int	y;
	int	cell;
	int	color;

	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	y = 0;
	while (cubed->data.map[y])
	{
		x = 0;
		while (cubed->data.map[y][x])
		{
			if (cubed->data.map[y][x] == '1')
				color = 0xFFFFFF;
			else if (cubed->data.map[y][x] == '0')
				color = 0x0FF000;
			else
				color = -1;
			if (color != -1)
				_s_draw_cell(cubed, x * cell, y * cell, cell, color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

