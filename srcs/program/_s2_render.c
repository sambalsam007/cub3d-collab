#include "cubed.h"

void	_s2_render_scene(t_cubed *c)
{

}

int	_s2_render_next_frame(t_cubed *cubed)
{

	reset_background(cubed);

	// update player
	update_player(cubed);
	int cell;
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);

	// calc


	// draw to window
	_s_draw_minimap(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, \
		cubed->mlx.img, 0, 0);




	return (SUCCESS);
}
