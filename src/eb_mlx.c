/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:40:48 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/14 21:40:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "wolf3d.h"

void	eb_put_pixel_to_img(t_data *d, int x, int y, int color)
{
	unsigned int	mgcv;
	int				i;

	mgcv = mlx_get_color_value(d->mlx, color);
	i = x * 4 + y * d->size_line;
	d->data[i] = (mgcv & 0xFF);
	d->data[i + 1] = (mgcv & 0xFF00) >> 8;
	d->data[i + 2] = (mgcv & 0xFF0000) >> 16;
}

int		eb_expose_hook(t_data *d)
{
	eb_clear_draw(d);
	eb_draw(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}

int		eb_mouse_hook(int button, int x, int y, t_data *d)
{
	(void)d;
	if (button == 1)
	{
		if ((*d->map->map[y / RA][x / RA] == d->map->wall)
			&& ((x / RA) != 0) && ((x / RA) != (d->map->x - 1))
			&& ((y / RA) != 0) && ((y / RA) != (d->map->y - 1)))
		{
			*d->map->map[y / RA][x / RA] = d->map->floor;
		}			
		else if (*d->map->map[y / RA][x / RA]
			!= *d->map->map[d->map->pos->y / RA][d->map->pos->x / RA])
		{
			*d->map->map[y / RA][x / RA] = d->map->wall;
		}
	}
	eb_expose_hook(d);
	ft_putstr("button : ");
	ft_putnbr(button);
	ft_putstr(",(x : ");
	ft_putnbr(x);
	ft_putstr(",y : ");
	ft_putnbr(y);
	ft_putstr(")\n");
	return (0);
}

int		eb_key_press(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_UP)
		d->save[0] = 1;
	if (keycode == KEY_DOWN)
		d->save[1] = 1;
	if (keycode == KEY_LEFT)
		d->save[2] = 1;
	if (keycode == KEY_RIGHT)
		d->save[3] = 1;
	return (0);
}

int		eb_key_release(int keycode, t_data *d)
{
	if (keycode == KEY_UP)
		d->save[0] = 0;
	if (keycode == KEY_DOWN)
		d->save[1] = 0;
	if (keycode == KEY_LEFT)
		d->save[2] = 0;
	if (keycode == KEY_RIGHT)
		d->save[3] = 0;
	return (0);
}

int		eb_loop_hook(t_data *d)
{
	if (d->save[0] == 1)
		eb_move_on(d);
	if (d->save[1] == 1)
		eb_move_back(d);
	if (d->save[2] == 1)
		eb_turn_left(d);
	if (d->save[3] == 1)
		eb_turn_right(d);
	eb_expose_hook(d);
	return (0);
}

int		eb_key_hook(int keycode, t_data *d)
{
	if (keycode == 65362)
		eb_move_on(d);
	else if (keycode == 65364)
	{
		eb_move_back(d);
		ft_putstr("DOWN\n");

		/*d->y += 10;
		d->map->pos->y += 10;*/
	}
	else if (keycode == 65361)
	{
		eb_turn_left(d);
		ft_putstr("LEFT\n");

	/*	if (d->x > 9)
			(d->x) -= 10;
		else
			(d->x) = 10;
		d->map->pos->x -= 10;*/
	}
	else if (keycode == 65363)
	{
		eb_turn_right(d);
		ft_putstr("RIGHT\n");

		/*(d->x) += 10;
		d->map->pos->x += 10;*/
	}
	else if (keycode == 65451)
	{
		d->width += 10;
		d->height += 10;
	}
	else if (keycode == 65453)
	{
		d->width -= 10;
		d->height -= 10;
	}
	else if (keycode == 65307)
		exit(0);
	else
	{
		ft_putstr("Keycode : ");
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	eb_expose_hook(d);
	return (0);
}

void	eb_mlx(t_data *d)
{
	d->mlx = mlx_init();
	d->x = 0;
	d->y = 0;
	d->width = WIDTH;
	d->height = HEIGHT;
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "Wolf3D");
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->data = mlx_get_data_addr(d->img, &d->bpp, &d->size_line, &d->endian);
	
	/*mlx_hook(d->win, 2, (1L << 0), eb_key_hook, d);*/
	mlx_mouse_hook(d->win, eb_mouse_hook, d);
	mlx_expose_hook(d->win, eb_expose_hook, d);
	mlx_hook(d->win, 2, 1, eb_key_press, d);
	mlx_hook(d->win, 3, 2, eb_key_release, d);
	mlx_loop_hook(d->mlx, eb_loop_hook, d);
	mlx_loop(d->mlx);
}

/*void	eb_mlx(t_data *d)
{
	d->mlx = mlx_init();
	d->x = 0;
	d->y = 0;
	d->width = 200;
	d->height = 200;
	d->win = mlx_new_window(d->mlx, d->map->x * RA, d->map->y * RA, "Wolf3D");
	d->img = mlx_new_image(d->mlx, d->map->x * RA, d->map->y * RA);
	d->data = mlx_get_data_addr(d->img, &d->bpp, &d->size_line, &d->endian);
	ft_putstr("TEST\n");
	mlx_hook(d->win, 2, (1L << 0), eb_key_hook, d);
	mlx_mouse_hook(d->win, eb_mouse_hook, d);
	mlx_expose_hook(d->win, eb_expose_hook, d);
	mlx_loop(d->mlx);
}*/
