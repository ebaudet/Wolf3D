/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 13:23:30 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/15 13:23:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

t_pos	*eb_search_wall(t_data *d, t_pos *pos, double alpha)
{
	t_pos	tmp;
	
	tmp.x = pos->x;
	tmp.y = pos->y;
	while (eb_collision(d, &tmp))
	{
		pos->x = tmp.x;
		pos->y = tmp.x;
		alpha = d->map->alpha;
		tmp.x = (int)(pos->x * cos(alpha) - pos->y * sin(alpha)) / RA;
		tmp.y = (int)(pos->x * sin(alpha) + pos->y * cos(alpha)) / RA;
		tmp.x += pos->x;
		tmp.y += pos->y;
	}
	return (pos);
}

void	eb_vision(t_data *d)
{
	t_pos	*pos;
	double	alpha;
	int		i;

	pos = NULL;
	eb_init_pos(d->map->pos->x, d->map->pos->y, pos);
	alpha = d->map->alpha;
	alpha = alpha - (0.017453 * 40);
	i = -1;
	while (++i < 80)
	{
		pos = eb_search_wall(d, pos, alpha);
		eb_trace_line(d, *pos, *(d->map->pos), 0xFFFFFF);
		pos->x = d->map->pos->x;
		pos->y = d->map->pos->y;
		alpha += 0.017453;
	}
}

int		eb_collision(t_data *d, t_pos *pos)
{
	if (*d->map->map[pos->y / RA][pos->x / RA] == d->map->wall)
		return (0);
	return (1);
}

void	eb_move_on(t_data *d)
{
	t_pos	pos;
	double	alpha;

	pos.x = d->map->pos->x;
	pos.y = d->map->pos->y;
	alpha = d->map->alpha;
	pos.x = (int)(pos.x * cos(alpha) - d->map->pos->y * sin(alpha)) / RA;
	pos.y = (int)(d->map->pos->x * sin(alpha) + pos.y * cos(alpha)) / RA;
	pos.x += d->map->pos->x;
	pos.y += d->map->pos->y;
	if (eb_collision(d, &pos) == 1)
	{
		d->map->pos->x = pos.x;
		d->map->pos->y = pos.y;
	}
	eb_vision(d);
}

void	eb_move_back(t_data *d)
{
	t_pos	pos;
	double	alpha;

	pos.x = d->map->pos->x;
	pos.y = d->map->pos->y;
	alpha = d->map->alpha;
	pos.x = (int)(pos.x * cos(alpha) - d->map->pos->y * sin(alpha)) / RA;
	pos.y = (int)(d->map->pos->x * sin(alpha) + pos.y * cos(alpha)) / RA;
	pos.x = d->map->pos->x - pos.x;
	pos.y = d->map->pos->y - pos.y;
	if (eb_collision(d, &pos) == 1)
	{
		d->map->pos->x = pos.x;
		d->map->pos->y = pos.y;
	}
}

void	eb_turn_right(t_data *d)
{
	d->map->alpha += 0.25;
}

void	eb_turn_left(t_data *d)
{
	d->map->alpha -= 0.25;
}
