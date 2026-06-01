/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 06:51:31 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/15 06:51:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

#define MINIMAP_RAYS 31

void	eb_trace_line(t_data *d, t_pos a, t_pos b, int color)
{
	int		x;
	int		y;

	if (a.x == b.x && a.y == b.y)
		return ;
	else if (eb_abs(b.x - a.x) >= eb_abs(b.y - a.y))
	{
		if (a.x > b.x)
			eb_swap_pos(&a, &b);
		x = a.x;
		while (x <= b.x)
		{
			y = a.y + ((b.y - a.y) * (x - a.x)) / (b.x - a.x);
			eb_put_pixel_to_img(d, x, y, color);
			x++;
		}
	}
	else
	{
		if (a.y > b.y)
			eb_swap_pos(&a, &b);
		y = a.y;
		while (y <= b.y)
		{
			x = a.x + ((b.x - a.x) * (y - a.y)) / (b.y - a.y);
			eb_put_pixel_to_img(d, x, y, color);
			y++;
		}
	}
}

void	eb_trace_block(t_data *d, int x, int y)
{
	t_line	*l1;
	t_line	*l2;
	t_line	*l3;
	t_line	*l4;

	if (*(d->map->map[y][x]) == d->map->wall)
	{
		l1 = eb_init_line(x * RM, y * RM, (x + 1) * RM, y * RM);
		l2 = eb_init_line((x + 1) * RM, y * RM, (x + 1) * RM, (y + 1) * RM);
		l3 = eb_init_line(x * RM, y * RM, x * RM, (y + 1) * RM);
		l4 = eb_init_line(x * RM, (y + 1) * RM, (x + 1) * RM, (y + 1) * RM);
		eb_trace_line(d, *l1->a, *l1->b, 0x0000ff);
		eb_trace_line(d, *l2->a, *l2->b, 0xff0000);
		eb_trace_line(d, *l3->a, *l3->b, 0x00ff00);
		eb_trace_line(d, *l4->a, *l4->b, 0xE8D630);
	}
}

static void	eb_trace_minimap_ray(t_data *d, double alpha)
{
	t_pos	pos;
	t_pos	start;
	t_pos	end;
	double	x;
	double	y;

	x = (double)d->map->pos->x;
	y = (double)d->map->pos->y;
	pos.x = d->map->pos->x;
	pos.y = d->map->pos->y;
	while (pos.x >= 0 && pos.y >= 0 && pos.x < d->map->x * RA
		&& pos.y < d->map->y * RA && eb_collision(d, &pos) <= 0)
	{
		x = x + cos(alpha);
		y = y + sin(alpha);
		pos.x = (int)x;
		pos.y = (int)y;
	}
	eb_init_pos((d->map->pos->x * RM) / RA,
		(d->map->pos->y * RM) / RA, &start);
	eb_init_pos((pos.x * RM) / RA, (pos.y * RM) / RA, &end);
	eb_trace_line(d, start, end, 0xFFFF00);
}

static void	eb_trace_minimap_vision(t_data *d)
{
	int		i;
	int		screen_x;
	double	dist_screen;
	double	alpha;

	i = 0;
	dist_screen = (WIDTH / 2) / tan((VISION * DEG_TO_RAD) / 2);
	while (i < MINIMAP_RAYS)
	{
		screen_x = -(WIDTH / 2) + ((WIDTH * i) / (MINIMAP_RAYS - 1));
		alpha = d->map->alpha + atan(screen_x / dist_screen);
		eb_trace_minimap_ray(d, alpha);
		i++;
	}
}

void	eb_trace_map(t_data *d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (d->map->map[i])
	{
		while (d->map->map[i][j])
		{
			eb_trace_block(d, j, i);
			j++;
		}
		j = 0;
		i++;
	}
	eb_trace_minimap_vision(d);
	eb_put_pixel_to_img(d, (d->map->pos->x * RM) / RA,
		(d->map->pos->y * RM) / RA, 0x000000);
}
