
#include "cubed.h"


/*
 * not necessary? 
 * remove
void draw_rays_on_map(t_cubed *g)
{
		float FOV = g->p.fov;

	int cell;
	if (get_cell_size(g, &cell, &cell) == ERROR)
			return ;

    int num_rays = 60; // number of rays for mini-map
    double start_angle = g->p.angle - (FOV / 2);
    double angle_step = FOV / num_rays;

    for (int i = 0; i < num_rays; i++) {
        double ray_angle = start_angle + i * angle_step;
        double length = _s_cast_ray(g, ray_angle, cell);

        // start position (p)
        double x0 = g->p.x / 4;
        double y0 = g->p.y / 4;

        // end position (ray hit)
        double x1 = x0 + (cos(ray_angle) * length / 4);
        double y1 = y0 + (sin(ray_angle) * length / 4);

        // simple line draw using Bresenham-like approach
        double dx = fabs(x1 - x0);
        double dy = fabs(y1 - y0);
        int steps = (dx > dy) ? dx : dy;
        double x_inc = (x1 - x0) / steps;
        double y_inc = (y1 - y0) / steps;
        double x = x0, y = y0;
        for (int j = 0; j <= steps; j++) {

				_s_my_mlx_pixel_put(g, (int)x, (int)y, 0xFFFFFF);
            // put_pixel(&g->img, (int)x, (int)y, 0x00FF00);
            x += x_inc;
            y += y_inc;
        }
    }
}
 */


double _s_cast_ray(t_cubed *cubed, double angle, int cell, int ray_nbr, float angle_step)
{
    // map dims (tiles)
    int map_h = 0;
    while (cubed->data.map[map_h])
        map_h++;
    int map_w = 0;
    for (int r = 0; r < map_h; r++)
    {
        int len = (int)strlen(cubed->data.map[r]);
        if (len > map_w) map_w = len;
    }
// player position in tiles (not pixels)
    double posX = cubed->p.x;
    double posY = cubed->p.y;

    // ray direction (per tile)
    double rayDirX = cos(angle);
    double rayDirY = sin(angle);

    // which box of the map we're in
    int mapX = (int)posX;
    int mapY = (int)posY;

    // length of ray from one x or y-side to next x or y-side
    // guard against zero:
    double deltaDistX = (fabs(rayDirX) > 1e-9) ? fabs(1.0 / rayDirX) : 1e9;
    double deltaDistY = (fabs(rayDirY) > 1e-9) ? fabs(1.0 / rayDirY) : 1e9;

    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;
    int side = 0; // 0 = x-side hit, 1 = y-side hit

    // DDA loop
    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        // bounds check
        if (mapX < 0 || mapY < 0 || mapX >= map_w || mapY >= map_h)
            break;

        // map stores chars like '1'/'0'
        if (cubed->data.map[mapY][mapX] == '1')
            hit = 1;
    }

    // compute perpendicular distance (in tiles), robust formula
    double perpDistTiles;
    if (side == 0)
        perpDistTiles = (mapX - posX + (1 - stepX) / 2.0) / ( (fabs(rayDirX) > 1e-9) ? rayDirX : 1e-9 );
    else
        perpDistTiles = (mapY - posY + (1 - stepY) / 2.0) / ( (fabs(rayDirY) > 1e-9) ? rayDirY : 1e-9 );

    // convert to absolute and to pixels
    double perpDistPixels = fabs(perpDistTiles) * cell;
	

	// for direction ray, skip all this stuff
	if (angle_step != -1);
	{

			// values found
			system("clear");
			printf("perp. distance (%fl)\n", perpDistPixels);

				// values to return / update
				printf("\n");
				printf("STRUCT angle (%f)\n", cubed->ray.angle);
				printf("STRUCT distance (%f)\n", cubed->ray.distance);
				printf("STRUCT hit x (%d)\n", cubed->ray.hit_x);
				printf("STRUCT hit y (%d)\n", cubed->ray.hit_y);
				printf("STRUCT side (%d)\n", cubed->ray.side);
				printf("STRUCT wall t (%lf)\n", cubed->ray.wall_t);
				printf("STRUCT wall b (%lf)\n", cubed->ray.wall_b);
				printf("STRUCT text x (%d)\n", cubed->ray.tex_x);
				printf("STRUCT text y (%d)\n", cubed->ray.tex_y);

			// updating stuff
				cubed->ray.distance = perpDistPixels;
				cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (ray_nbr * angle_step);
	}

		// return deze afstand voor de 'direction ray'
    return perpDistPixels;
}

// is not using DDA algo,
// just naive pixel stepping
void _s_draw_ray_line(t_cubed *cubed, double angle, int cell)
{
    // compute map dimensions for put_pixel bounds
    int map_h = 0;
    while (cubed->data.map[map_h])
        map_h++;
    int map_w = 0;
    for (int r = 0; r < map_h; r++)
    {
        int len = (int)strlen(cubed->data.map[r]);
        if (len > map_w) map_w = len;
    }
    int map_w_px = map_w * cell;
    int map_h_px = map_h * cell;

	// add -1 for drawing the direction line
    double dist_px = _s_cast_ray(cubed, angle, cell, -1, -1);

    double startX = cubed->p.x * cell;
    double startY = cubed->p.y * cell;
    double dx = cos(angle);
    double dy = sin(angle);

    int steps = (int)(dist_px); // step per pixel
    if (steps < 0) steps = 0;

    for (int i = 0; i <= steps; i++)
    {
        int x = (int)round(startX + dx * i);
        int y = (int)round(startY + dy * i);
        _s_my_mlx_pixel_put(cubed, x, y, 0x000000);
        // put_pixel(cubed, x, y, 0x000000, map_w_px, map_h_px);
    }

    // mark hit point in red (clamped)
    int endx = (int)round(startX + dx * dist_px);
    int endy = (int)round(startY + dy * dist_px);
    _s_my_mlx_pixel_put(cubed, endx, endy, 0xFF0000);
    // put_pixel(cubed, endx, endy, 0xFF0000, map_w_px, map_h_px);
}

