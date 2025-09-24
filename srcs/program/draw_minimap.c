#include "cubed.h"

// helper to draw a filled square cell
static void	temp_draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
			my_mlx_pixel_put(cubed, x + i, y + j, color);
	}
}

// helper to draw a small circle for the player
static void	temp_draw_circle(t_cubed *cubed, int cx, int cy, int r, int color)
{
	for (int y = -r; y <= r; y++)
	{
		for (int x = -r; x <= r; x++)
		{
			if (x * x + y * y <= r * r)
				my_mlx_pixel_put(cubed, cx + x, cy + y, color);
		}
	}
}

// optional line drawing (for rays on minimap)
static void	temp_draw_line(t_cubed *cubed, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		my_mlx_pixel_put(cubed, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

void	temp_draw_minimap(t_cubed *cubed)
{
	int scale = cubed->minimap.scale;
	if (scale <= 0)
		scale = 4; // default small scale
	scale = 40; // TODO remove this.

	// draw map tiles
	for (int y = 0; cubed->data.map[y]; y++)
	{
		for (int x = 0; cubed->data.map[y][x]; x++)
		{
			if (cubed->data.map[y][x] == '1')
				temp_draw_cell(cubed, x * scale, y * scale, scale, 0xFFFFFF); // walls = white
			else
				temp_draw_cell(cubed, x * scale, y * scale, scale, 0x000000); // empty = black
		}
	}

	// draw player
	int px = (int)(cubed->p.x * scale);
	int py = (int)(cubed->p.y * scale);
	temp_draw_circle(cubed, px, py, scale / 2, 0xFF0000); // player = red

	// optional: draw rays
	temp_draw_line(cubed, px, py,
		(int)(cubed->minimap.first_x * scale),
		(int)(cubed->minimap.first_y * scale),
		0x00FF00); // first ray = green

	temp_draw_line(cubed, px, py,
		(int)(cubed->minimap.last_x * scale),
		(int)(cubed->minimap.last_y * scale),
		0x0000FF); // last ray = blue
}

