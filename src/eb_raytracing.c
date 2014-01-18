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

	dist = 0;
	x = (double)pos->x;
	y = (double)pos->y;
	/*printf("y,y = (%d, %d)(%f, %f)+", pos->x, pos->y, x, y);*/
	while (!eb_collision(d, pos))
	{
		eb_put_pixel_to_img(d, (pos->x * RM) / RA, (pos->y * RM) / RA, 0xFFFFFF);
		pos->x = (int)x;
		pos->y = (int)y;
		x = x + (cos(alpha) * 1);
		y = y + (sin(alpha) * 1);
		dist += 1;
		/*printf("-");*/
	}
	col->face = eb_collision(d, pos);
	col->dist = (double)dist;
	/*printf("eb_search_wall:dist %f, dist : %d | retour col : %d\n", col->dist, dist, eb_collision(d, pos));*/
}

void	eb_vision(t_data *d)
{
	t_pos		*pos;
	double		alpha;
	int			i;
	double		dist_screen;
	t_colision	*col;

	dist_screen = (WIDTH / 2) / tan((VISION * DEG_TO_RAD) / 2);
	pos = (t_pos *)malloc(sizeof(t_pos));
	col = (t_colision *)malloc(sizeof(t_colision));
	eb_init_pos(d->map->pos->x, d->map->pos->y, pos);
	/*alpha = d->map->alpha;
	alpha = alpha - (0.002181 * 240);*/
	/*printf("d->map->alpha : %f\n", d->map->alpha);*/
	i = -(WIDTH / 2) - 1;
	while (++i <= (WIDTH / 2))
	{
		alpha = d->map->alpha;
		alpha += atan(i / dist_screen);
		/*printf("%f\n", alpha);*/
		eb_search_wall(d, pos, alpha, col);
		/*printf("eb_vision:dist %f\n", col->dist);*/
		col->dist = col->dist * cos(alpha - d->map->alpha);
		eb_print_wolf(d, col, dist_screen, i + (WIDTH / 2) - 1);

		pos->x = d->map->pos->x;
		pos->y = d->map->pos->y;
	}

	free(pos);
}

void	eb_print_wolf(t_data *d, t_colision *col, double dist_screen, int i)
{
	double		height;
	t_pos	a;
	t_pos	b;
	int		ya;
	int		yb;

	/*printf("eb_print_wolf:dist %f\n", col->dist);*/
	height = ((dist_screen * (double)HEIGHT) / col->dist);
	height = height / 10;
	/*printf("height : %d\n", height);*/
	ya = (d->map->axis_y - (int)(height / 2));
	ya = (ya <= 0 ? 1 : ya);
	yb = (d->map->axis_y + (int)(height / 2));
	yb = (yb >= HEIGHT ? HEIGHT : yb);
	/*printf("color = %f \t", (dist / MAXLEN));*/
	eb_init_pos(i, ya, &a);
	eb_init_pos(i, yb, &b);
	/*eb_trace_line(d, a, b, 0xFFFFFF * ((dist * 2) / MAXLEN));*/
	
	if (col->face == 1)
	{
		eb_trace_line(d, a, b, 0xFF0000);
	}
	else if (col->face == 2)
	{
		eb_trace_line(d, a, b, 0x00FF00);
	}
	else if (col->face == 3)
	{
		eb_trace_line(d, a, b, 0x0000FF);
	}
	else if (col->face == 4)
	{
		eb_trace_line(d, a, b, 0xFF7F00);
	}
	else
	{
		eb_trace_line(d, a, b, 0xFFFFFF);
	}
}
