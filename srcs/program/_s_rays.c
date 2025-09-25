
#include "cubed.h"


// samuel edit 09.25
// calculates tex_x tex_y
void _s_calc_tex_x_tex_y(t_cubed *cubed, int i, t_ray *ray, t_tex tex)
{
    // use ray->tex_x instead of ray.tex_x
    double perpDist = ray->distance * cos(ray->angle - cubed->p.angle);
    if (perpDist < 1e-6)
        perpDist = 1e-6;

    int lineHeight = (int)(HEIGHT / perpDist);

    double wallX;
    if (ray->side == NORTH || ray->side == SOUTH)
        wallX = cubed->p.x + perpDist * cos(ray->angle);
    else
        wallX = cubed->p.y + perpDist * sin(ray->angle);
    wallX -= floor(wallX);

    ray->tex_x = (int)(wallX * (double)tex.width);
    if (ray->side == SOUTH || ray->side == WEST)
        ray->tex_x = tex.width - ray->tex_x - 1;

    double step = (double)tex.height / lineHeight;
    double texPos = (-(lineHeight / 2.0) + (HEIGHT / 2.0)) * step;

    int y = (HEIGHT / 2) - (lineHeight / 2);
    if (y < 0) y = 0;
    while (y < (HEIGHT / 2 + lineHeight / 2) && y < HEIGHT)
    {
        ray->tex_y = (int)texPos & (tex.height - 1);
        texPos += step;
        // int color = *(unsigned int *)(tex.adr + (ray->tex_y * tex.size_line + ray->tex_x * (tex.bpp / 8)));
        // my_mlx_pixel_put(cubed, i, y, color);
        y++;
    }
}

void	_s_display_ray_struct_info(t_cubed *cubed, int i)
{

		// print variables
		system("clear");
		printf("MIDDLE RAY / DIRECTION RAY\n");
		printf("Angle\t[%d] (%f)\n", i, cubed->ray.angle);
		printf("Distn\t[%d] (%f)\n", i, cubed->ray.distance);
		printf("hit_x\t[%d] (%d)\n", i, cubed->ray.hit_x);
		printf("hit_y\t[%d] (%d)\n", i, cubed->ray.hit_y);
		if (cubed->ray.side == NORTH) printf("side\t[%d] (NORTH)\n", i);
		else if (cubed->ray.side == SOUTH) printf("side\t[%d] (SOUTH)\n", i);
		else if (cubed->ray.side == EAST) printf("side\t[%d] (EAST)\n", i);
		else if (cubed->ray.side == WEST) printf("side\t[%d] (WEST)\n", i);
		printf("wall_t\t[%d] (%lf)\n", i, cubed->ray.wall_t);
		printf("wall_b\t[%d] (%lf)\n", i, cubed->ray.wall_b);
		printf("tex_x\t[%d] (%d)\n", i, cubed->ray.tex_x);
		printf("tex_y\t[%d] (%d)\n", i, cubed->ray.tex_y);
		printf("\n");
}

t_compas _s_get_compass(int side, double rayDirX, double rayDirY)
{
    if (side == 0) // hit vertical wall
    {
        if (rayDirX > 0)
            return EAST;
        else
            return WEST;
    }
    else // hit horizontal wall
    {
        if (rayDirY > 0)
            return SOUTH;
        else
            return NORTH;
    }
}


double _s_cast_ray(t_cubed *cubed, double angle, int cell)
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

	// COMPASS
	t_compas side_dir = _s_get_compass(side, rayDirX, rayDirY);

	// Calc Texture ====


	// ==== Calc Texture 

    // compute perpendicular distance (in tiles), robust formula
    double perpDistTiles;
    if (side == 0)
        perpDistTiles = (mapX - posX + (1 - stepX) / 2.0) / ( (fabs(rayDirX) > 1e-9) ? rayDirX : 1e-9 );
    else
        perpDistTiles = (mapY - posY + (1 - stepY) / 2.0) / ( (fabs(rayDirY) > 1e-9) ? rayDirY : 1e-9 );



    // hit world position in pixels
    double hitX = (posX + rayDirX * perpDistTiles) * cell;
    double hitY = (posY + rayDirY * perpDistTiles) * cell;

    // convert to absolute distance (pixels)
    double perpDistPixels = fabs(perpDistTiles) * cell;

    // store or return as needed
    cubed->ray.hit_x = hitX;
    cubed->ray.hit_y = hitY;
    cubed->ray.side  = side_dir;  // optional, for shading/tex

    return perpDistPixels;
}

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

    double dist_px = _s_cast_ray(cubed, angle, cell);

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
        my_mlx_pixel_put(cubed, x, y, 0x000000);
        // put_pixel(cubed, x, y, 0x000000, map_w_px, map_h_px);
    }

    // mark hit point in red (clamped)
    int endx = (int)round(startX + dx * dist_px);
    int endy = (int)round(startY + dy * dist_px);
    my_mlx_pixel_put(cubed, endx, endy, 0xFF0000);
    // put_pixel(cubed, endx, endy, 0xFF0000, map_w_px, map_h_px);
}

int	_s_make_ray_calculations(t_cubed *cubed, int i, float angle_step, int cell)
{
		// calculate ray angle
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);

		// calculate distance until it hits a wall
		// The distance returned by _s_cast_ray is already perpendicular,
		// meaning: it's already corrected for the fish-eye stuff
		cubed->ray.distance = _s_cast_ray(cubed, cubed->ray.angle, cell);

		// wall
        double wall_height = (TILE_SIZE * HEIGHT) / cubed->ray.distance; // ray.distance must be fish-eye corrected
        cubed->ray.wall_t = (HEIGHT / 2) - (wall_height / 2);
        cubed->ray.wall_b = (HEIGHT / 2) + (wall_height / 2);

		// updates the tex_x and tex_y
		// need to rename it
		_s_calc_tex_x_tex_y(cubed, i, &cubed->ray, cubed->texture[cubed->ray.side]);

		// TODO decent return statement
		return 0;
}
