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

#include "wolf3d.h"

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
}
