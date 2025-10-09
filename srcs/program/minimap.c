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
	int		x;
	int		y;
	int		cell;
	int		color;
	int		scale;
	int		offset_x;
	int		offset_y;

	// original cell size
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);

	// shrink to 30%
	scale = (int)(cell * 0.3);

	// place minimap in top-right
	// width of minimap = num_cols * scale
	int map_width = ft_strlen(cubed->data.map[0]) * scale;
	int map_height = 0;
	while (cubed->data.map[map_height])
		map_height++;

	map_height *= scale;

	offset_x = WIDTH - map_width - 10; // 10px margin from right
	offset_y = 10;                     // 10px margin from top

	y = 0;
	while (cubed->data.map[y])
	{
		x = 0;
		while (cubed->data.map[y][x])
		{
			if (cubed->data.map[y][x] == '1')
				color = 0xFFFFFF; // wall
			else if (cubed->data.map[y][x] == '0')
				color = 0x00FF00; // floor
			else
				color = -1;
			if (color != -1)
				_s_draw_cell(cubed,
					offset_x + x * scale,
					offset_y + y * scale,
					scale,
					color);
			x++;
		}
		y++;
	}
	_s_draw_player(cubed, cubed->p, scale, offset_x, offset_y);

	return (SUCCESS);
}

