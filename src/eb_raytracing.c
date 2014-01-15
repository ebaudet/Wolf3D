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

int		eb_search_wall(t_data *d, t_pos *pos, double alpha)
{
	int		dist;

	dist = 0;
	double	x;
	double	y;
	x = (double)pos->x;
	y = (double)pos->y;
	while (eb_collision(d, pos))
	{
		eb_put_pixel_to_img(d, pos->x, pos->y, 0xFFFFFF);
		pos->x = (int)x;
		pos->y = (int)y;
		x = x + (cos(alpha) * 1);
		y = y + (sin(alpha) * 1);
		dist++;
	}
	return (dist);
}

void	eb_vision(t_data *d)
{
	t_pos	*pos;
	double	alpha;
	int		i;

	pos = (t_pos *)malloc(sizeof(t_pos));
	eb_init_pos(d->map->pos->x, d->map->pos->y, pos);
	alpha = d->map->alpha;
	alpha = alpha - (0.002181 * 240);
	i = -1;
	while (++i < 480)
	{
		eb_search_wall(d, pos, alpha);
		pos->x = d->map->pos->x;
		pos->y = d->map->pos->y;
		alpha += 0.002181;
	}
	free(pos);
}
