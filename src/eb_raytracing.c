/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_raytracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 18:49:28 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/15 18:49:28 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "wolf3d.h"
#include <stdio.h>

void	eb_search_wall(t_data *d, t_pos *pos, double alpha, t_colision *col)
{
	int		dist;
	double	x;
	double	y;
	int		colision;

	dist = 0;
	x = (double)pos->x;
	y = (double)pos->y;
	d->inter_colision = 0;
	while ((colision = eb_collision(d, pos)) <= 0)
	{
		if (d->save[4])
			eb_put_pixel_to_img(d, (pos->x * RM) / RA, (pos->y * RM) / RA,
				colision == -1 ? 0x23eb67 : 0xFFFFFF);
		if (colision < 0)
			d->inter_colision = colision;
		pos->x = (int)x;
		pos->y = (int)y;
		x = x + (cos(alpha) * 1);
		y = y + (sin(alpha) * 1);
		dist += 1;
	}
	col->face = colision;
	col->dist = (double)dist;
}

void	eb_vision(t_data *d)
{
	t_pos		*pos;
	double		alpha;
	int			x;
	t_colision	*col;

	d->dist_screen = (WIDTH / 2) / tan((VISION * DEG_TO_RAD) / 2);
	pos = (t_pos *)malloc(sizeof(t_pos));
	col = (t_colision *)malloc(sizeof(t_colision));
	eb_init_pos(d->map->pos->x, d->map->pos->y, pos);
	/*alpha = d->map->alpha;
	alpha = alpha - (0.002181 * 240);*/
	/*printf("d->map->alpha : %f\n", d->map->alpha);*/
	x = -(WIDTH / 2) - 1;
	while (++x <= (WIDTH / 2))
	{
		alpha = d->map->alpha + atan(x / d->dist_screen);
		/*printf("%f\n", alpha);*/
		eb_search_wall(d, pos, alpha, col);
		/*printf("eb_vision:dist %f\n", col->dist);*/
		col->dist = col->dist * cos(atan(x / d->dist_screen));
		eb_print_wall(d, col, x + (WIDTH / 2) - 1);
		eb_floor_casting(d, pos, col, alpha);
		pos->x = d->map->pos->x;
		pos->y = d->map->pos->y;
	}

	free(pos);
}

void	eb_print_wall(t_data *d, t_colision *col, int x)
{
	double		height;
	t_pos	a;
	t_pos	b;
	int		ya;
	int		yb;

	/*printf("eb_print_wolf:dist %f\n", col->dist);*/
	height = ((d->dist_screen * (double)HEIGHT) / col->dist);
	height = height / 10;
	/*printf("height : %d\n", height);*/
	ya = (d->map->axis_y - (int)(height / 2));
	ya = (ya <= 0 ? 1 : ya);
	yb = (d->map->axis_y + (int)(height / 2));
	yb = (yb >= HEIGHT ? HEIGHT : yb);
	/*printf("color = %f \t", (dist / MAXLEN));*/
	eb_init_pos(x, ya, &a);
	eb_init_pos(x, yb, &b);
	/*eb_trace_line(d, a, b, 0xFFFFFF * ((dist * 2) / MAXLEN));*/

	if (col->face == 1)
		eb_trace_line(d, a, b, color_shadow(0xFF0000, 500 / col->dist));
	else if (col->face == 2)
		eb_trace_line(d, a, b, color_shadow(0x00FF00, 500 / col->dist));
	else if (col->face == 3)
		eb_trace_line(d, a, b, color_shadow(0x0000FF, 500 / col->dist));
	else if (col->face == 4)
		eb_trace_line(d, a, b, color_shadow(0xFF7F00, 500 / col->dist));
	else
		eb_trace_line(d, a, b, color_shadow(0xFFFFFF, 500 / col->dist));
}

void	eb_floor_casting(t_data *d, t_pos *pos, t_colision *col, double alpha)
{
	int		dist;
	double	x;
	double	y;
	int		colision;

	if (d->inter_colision == 0)
		return;
	dist = 0;
	x = (double)pos->x;
	y = (double)pos->y;
	while ((colision = eb_collision(d, pos)) <= 0)
	{
		if (colision < 0)
			eb_print_wend(d, alpha, dist, col->dist);
		pos->x = (int)x;
		pos->y = (int)y;
		x = x + (cos(alpha) * 1);
		y = y + (sin(alpha) * 1);
		dist += 1;
	}
}

void	eb_print_wend(t_data *d, double alpha, int dist, double dist_wall)
{
	double		height = ((d->dist_screen * (double)HEIGHT) / dist_wall) / 20;
	double hipotenus_wall = height / sin(alpha);
	double dist_wall_screen = (((double)HEIGHT / 2) / sin(alpha)) - hipotenus_wall;
	double dist_floor_screen = dist * dist_wall_screen / dist_wall;
	// alpha += d->map->alpha;
	double y = (HEIGHT - dist_floor_screen * sin(alpha)) / 2 + HEIGHT / 2;
	double x = WIDTH / 2 + dist_floor_screen * cos(alpha);
	// x *= -1;
	// double d->dist_screen = (WIDTH / 2) / tan((VISION * DEG_TO_RAD) / 2);
	// printf("x = %f, y = %f\n", x, y);

	x = (x >= WIDTH ? WIDTH : x);
	x = x < 0 ? 0 : x;
	y = (y >= HEIGHT ? HEIGHT : y);
	y = y < 0 ? 0 : y;
	eb_put_pixel_to_img(d, (int)x, (int)y, 0x23eb67);
}

/*
void floor_casting(t_data *d, double alpha)
{
	//FLOOR CASTING
      double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
      if(side == 0 && rayDirX > 0)
      {
        floorXWall = d->map->x;
        floorYWall = d->map->y + wallX;
      }
      else if(side == 0 && rayDirX < 0)
      {
        floorXWall = d->map->x + 1.0;
        floorYWall = d->map->y + wallX;
      }
      else if(side == 1 && rayDirY > 0)
      {
        floorXWall = d->map->x + wallX;
        floorYWall = d->map->y;
      }
      else
      {
        floorXWall = d->map->x + wallX;
        floorYWall = d->map->y + 1.0;
      }

      double distWall, distPlayer, currentDist;

      distWall = perpWallDist;
      distPlayer = 0.0;

      if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows

      //draw the floor from drawEnd to the bottom of the screen
      for(int y = drawEnd + 1; y < h; y++)
      {
        currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

        int floorTexX, floorTexY;
        floorTexX = int(currentFloorX * texWidth) % texWidth;
        floorTexY = int(currentFloorY * texHeight) % texHeight;

        //floor
        buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
        //ceiling (symmetrical!)
        buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
      }
}
*/
