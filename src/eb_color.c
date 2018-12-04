/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 21:25:38 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/13 21:25:38 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		color_shadow(int color, double shadow)
{
	int		red;
	int		green;
	int		blue;

	red = (color >> 16) % 256;
	green = (color >> 8) % 256;
	blue = color % 256;
	red = red * shadow;
	green = green * shadow;
	blue = blue * shadow;
	color = color_norm(red, green, blue);
	return (color);
}

int		color_norm(int red, int green, int blue)
{
	int		color;

	red = (red > 0xFF ? 0xFF : red);
	green = (green > 0xFF ? 0xFF : green);
	blue = (blue > 0xFF ? 0xFF : blue);
	red = (red < 0x00 ? 0x00 : red);
	green = (green < 0x00 ? 0x00 : green);
	blue = (blue < 0x00 ? 0x00 : blue);
	color = (red << 16) + (green << 8) + blue;
	return (color);
}
