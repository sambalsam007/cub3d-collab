#include "cubed.h"

// write the pixel color into the image buffer (at x,y)
// x = the x coordinate of the pixel
// y = y coord... pixel
void	_s_my_mlx_pixel_put(t_cubed *cubed, int x, int y, int color)
{
	char	*dst;

	// dst = the spot in the mlx address that we are going to edit
	// calculate:
	// 		starting point of the address
	// 		+ (formula to calculate place for x y coordinate)
	dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

// func: draw certain cell/tile on the img, in true size (so at its pixel position)
// input:
// x = PIXEL x position of the top-left corner of the cell/tile
// y = PIXEL y position of the top left corner of the cell/tile
// int size = PIXEL size 1 cell/tile (H, L)
// color = color to use
void	_s_draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	int	i;
	int	j;

	// loop over every pixel inside one cell
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
				// x, y are top left corner
				// so we do x+i and y+j to fill the entire cell
				// we draw a pixel at (x+i, y+j)
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

	// gives pixel size of a tile on the minimap
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	y = 0;

	// go through the map rows
	while (cubed->data.map[y])
	{
		x = 0;
		// got through map by columns (iterate per character)
		while (cubed->data.map[y][x])
		{
				// color for wall
				// color for floor
				// not wall / floor? => do not draw
			if (cubed->data.map[y][x] == '1')
				color = 0xFFFFFF;
			else if (cubed->data.map[y][x] == '0')
				color = 0x0FF000;
			else
				color = -1; // if it's not a wall & not floor , dont draw
			if (color != -1) // if = wall or floor, draw it
				_s_draw_cell(cubed, x * cell, y * cell, cell, color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

