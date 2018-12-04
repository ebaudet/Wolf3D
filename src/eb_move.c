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

#include <stdio.h>
#include <math.h>
#include "wolf3d.h"

int		eb_collision(t_data *d, t_pos *pos)
{
	if (*d->map->map[pos->y / RA][pos->x / RA] == d->map->wall)
	{
		if (pos->x == ((pos->x / RA) * RA))
			return (1);
		else if (pos->x == (((pos->x / RA) + 1) * RA - 1))
			return (2);
		else if (pos->y == ((pos->y / RA) * RA))
			return (3);
		else if (pos->y == (((pos->y / RA) + 1) * RA - 1))
			return (4);
		else
			return (5);

	}
	return (0);
}

void	eb_move_on(t_data *d)
{
	t_pos	pos;
	double	alpha;

	pos.x = d->map->pos->x;
	pos.y = d->map->pos->y;
	alpha = d->map->alpha;
	pos.x = d->map->pos->x + (int)(cos(alpha) * 25);
	pos.y = d->map->pos->y + (int)(sin(alpha) * 25);
	if (eb_collision(d, &pos) == 0)
	{
		d->map->pos->x = pos.x;
		d->map->pos->y = pos.y;
	}
}

void	eb_move_back(t_data *d)
{
	t_pos	pos;
	double	alpha;

	pos.x = d->map->pos->x;
	pos.y = d->map->pos->y;
	alpha = d->map->alpha;
	pos.x = d->map->pos->x - (int)(cos(alpha) * 25);
	pos.y = d->map->pos->y - (int)(sin(alpha) * 25);
	if (eb_collision(d, &pos) == 0)
	{
		d->map->pos->x = pos.x;
		d->map->pos->y = pos.y;
	}
}

void	eb_turn_right(t_data *d)
{
	d->map->alpha += 5 * DEG_TO_RAD;
}

void	eb_turn_left(t_data *d)
{
	d->map->alpha -= 5 * DEG_TO_RAD;
}
