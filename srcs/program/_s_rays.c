
#include "cubed.h"

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

    // compute perpendicular distance (in tiles), robust formula
    double perpDistTiles;
    if (side == 0)
        perpDistTiles = (mapX - posX + (1 - stepX) / 2.0) / ( (fabs(rayDirX) > 1e-9) ? rayDirX : 1e-9 );
    else
        perpDistTiles = (mapY - posY + (1 - stepY) / 2.0) / ( (fabs(rayDirY) > 1e-9) ? rayDirY : 1e-9 );

    // convert to absolute and to pixels
    double perpDistPixels = fabs(perpDistTiles) * cell;
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
        _s_my_mlx_pixel_put(cubed, x, y, 0x000000);
        // put_pixel(cubed, x, y, 0x000000, map_w_px, map_h_px);
    }

    // mark hit point in red (clamped)
    int endx = (int)round(startX + dx * dist_px);
    int endy = (int)round(startY + dy * dist_px);
    _s_my_mlx_pixel_put(cubed, endx, endy, 0xFF0000);
    // put_pixel(cubed, endx, endy, 0xFF0000, map_w_px, map_h_px);
}

