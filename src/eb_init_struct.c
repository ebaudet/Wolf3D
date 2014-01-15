/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 11:04:39 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/15 11:04:39 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

void	eb_init_pos(int x, int y, t_pos *pos)
{
	pos->x = x;
	pos->y = y;
}

void	eb_init_line_pos(t_pos *a, t_pos *b, t_line *line)
{
	line->a = a;
	line->b = b;
}

t_line	*eb_init_line(int xa, int ya, int xb, int yb)
{
	t_line		*line;
	t_pos		*a;
	t_pos		*b;

	line = (t_line *)malloc(sizeof(t_line));
	a = (t_pos *)malloc(sizeof(t_pos));
	b = (t_pos *)malloc(sizeof(t_pos));
	a->x = xa;
	a->y = ya;
	b->x = xb;
	b->y = yb;
	line->a = a;
	line->b = b;
	return (line);
}
