/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 06:53:50 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/15 06:53:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

void	eb_clean_map(t_data *d)
{
	int		x;
	int		y;

	x = 0;
	while (x <= WIDTH / 5)
	{
		y = 0;
		while (y <= HEIGHT / 5)
		{
			eb_put_pixel_to_img(d, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

void	eb_draw(t_data *d)
{
	
	/*eb_put_pixel_to_img(d, d->map->pos->x, d->map->pos->y, 0xBD33A4);
	eb_put_pixel_to_img(d, d->map->pos->x + 1, d->map->pos->y, 0xBD33A4);
	eb_put_pixel_to_img(d, d->map->pos->x, d->map->pos->y + 1, 0xBD33A4);
	eb_put_pixel_to_img(d, d->map->pos->x + 1, d->map->pos->y + 1, 0xBD33A4);*/
	/*eb_clean_map(d);*/
	eb_vision(d);

	/*printf("(%d, %d)\n", d->map->pos->x, d->map->pos->y);*/
	eb_put_pixel_to_img(d, (d->map->pos->x  * RM) / RA, (d->map->pos->y * RM) / RA, 0x000000);
	eb_trace_map(d);

	/*int		x;
	int		y;*/
	/*t_pos	a1;
	t_pos	b1;
	t_pos	a2;
	t_pos	b2;
	t_pos	a3;
	t_pos	b3;
	t_pos	a4;
	t_pos	b4;

	eb_init_pos(0, 0, &a1);
	eb_init_pos(d->x, d->y, &b1);
	eb_init_pos(WIDTH, 0, &a2);
	eb_init_pos(d->x + d->width, d->y, &b2);
	eb_init_pos(0, HEIGHT, &a3);
	eb_init_pos(d->x, d->y + d->height, &b3);
	eb_init_pos(WIDTH, HEIGHT, &a4);
	eb_init_pos(d->x + d->width, d->y + d->height, &b4);*/

	/*x = d->x;
	while (x < (d->x + d->width))
	{
		y = d->y;
		while (y < (d->y + d->height))
		{
			eb_put_pixel_to_img(d, x, y, 0xFF0000);
			y++;
		}
		x++;
	}*/
	/*eb_trace_line(d, a1, b1, 0x00FF00);
	eb_trace_line(d, a2, b2, 0x00FF00);
	eb_trace_line(d, a3, b3, 0x00FF00);
	eb_trace_line(d, a4, b4, 0x00FF00);

	eb_trace_line(d, b1, b2, 0x00FF00);
	eb_trace_line(d, b4, b2, 0x00FF00);
	eb_trace_line(d, b3, b4, 0x00FF00);
	eb_trace_line(d, b3, b1, 0x00FF00);*/

}

void	eb_clear_draw(t_data *d)
{
	int		x;
	int		y;

	x = 0;
	while (x <= WIDTH)
	{
		y = 0;
		while (y <= (HEIGHT / 2))
		{
			eb_put_pixel_to_img(d, x, y, 0xBBBBBB);
			y++;
		}
		while (y <= HEIGHT)
		{
			eb_put_pixel_to_img(d, x, y, 0x444444);
			y++;
		}
		x++;
	}
}
