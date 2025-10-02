#include "cubed.h"

int	_s2_render_next_frame(t_cubed *cubed)
{

	// draw minimap n player
	int cell;
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	_s_draw_minimap(cubed);
	_s_draw_player(cubed, cubed->p, cell);


	/*
	// move player Forw. Backw.
	double moveStep = 0.0;
	if (cubed->keys['w']) 
		moveStep += MOVE_SPEED;
	if (cubed->keys['s']) 
		moveStep -= MOVE_SPEED;

	if (moveStep != 0.0) {
		double nx = cubed->p.x + cubed->p.dirX * moveStep;
		double ny = cubed->p.y + cubed->p.dirY * moveStep;
		// ** if we moved, calculate the new player position
		if (can_move(cubed, nx, ny))
		{
			cubed->p.x = nx;
			cubed->p.y = ny;
		}
		// ** check if there is the player can move, 
		// ** if there is no wall.
		// ** if the player can move, update the player position
	}

	
	printf("w key (%d)\n", cubed->keys['w']);
	printf("movestep (%lf)\n", moveStep);
	printf("movespeed (%f)\n", MOVE_SPEED);
	*/

	// put img to window
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, \
		cubed->mlx.img, 0, 0);




	return (SUCCESS);
}
