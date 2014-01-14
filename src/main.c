/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 18:37:52 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/13 18:37:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void        ft_print_map(int ***map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			ft_putnbr(*map[i][j]);
			ft_putchar(' ');
			j++;
		}
		j = 0;
		ft_putchar('\n');
		i++;
	}
}

int		main(int ac, char *av[])
{
	t_map	*map;

	if (ac != 2)
		eb_perror("usage : ./wolf3d map");
	map = eb_getdata(--ac, ++av);
	ft_print_map(map->map);
	return (0);
}
