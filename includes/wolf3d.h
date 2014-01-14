/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 18:53:43 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/13 18:53:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "../libft/includes/libft.h"

typedef struct		s_map
{
	int				x;
	int				y;
	char			*name;
	int				wall;
	int				floor;
	int				start;
	int				***map;
}					t_map;

/*
** eb_error.c
*/
int		eb_perror(char *str);

/*
** eb_getdata.c
*/
t_map	*eb_getdata(int ac, char *av[]);
t_map	*eb_init_t_map(t_map *map, char *str);
void	eb_map_init(t_map *map, char *str, int line);

#endif /* !WOLF3D_H */
