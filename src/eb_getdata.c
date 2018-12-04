/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eb_getdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 21:25:38 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/13 21:25:38 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "wolf3d.h"
#include <stdio.h>

t_map	*eb_getdata(char *av[])
{
	int		fd;
	char	*line;
	int		i;
	t_map	*map;
	t_map	*temp;

	map = NULL;
	if ((fd = open(*av, O_RDONLY)) < 0)
		eb_perror("Mauvaise ouverture du fichier");
	while (get_next_line(fd, &line) > 0)
	{
		temp = NULL;
		temp = eb_init_t_map(temp, line);
		i = -1;
		while (++i < temp->y && get_next_line(fd, &line) > 0)
			eb_map_init(temp, line, i);
		printf("map: x=%d, y=%d, name=%s, wall=%d, floor=%d, start=%d, end=%d\n",
		       temp->x, temp->y, temp->name, temp->wall, temp->floor, temp->start, temp->end);
		map = eb_map_add_to_queue(map, temp);
	}
	if (close(fd) < 0)
		eb_perror("Mauvaise fermeture de filedescriptor");
	return (map);
}

t_map	*eb_init_t_map(t_map *map, char *str)
{
	char	**tab;
	int		i;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	tab = ft_strsplit(str, ' ');
	printf("sizeof('tab') = %lu\n", sizeof(tab[1]));
	map->x = ft_atoi(tab[0]);
	map->y = ft_atoi(tab[1]);
	map->name = ft_strdup(tab[2]);
	map->wall = ft_atoi(tab[3]);
	map->floor = ft_atoi(tab[4]);
	map->start = ft_atoi(tab[5]);
	if (tab[6])
		map->end = ft_atoi(tab[6]);
	else
		map->end = -1;
	map->pos = (t_pos *)ft_memalloc(sizeof(t_pos));
	map->map = (int ***)ft_memalloc(sizeof(int **) * (map->y + 1));
	map->alpha = 0;
	map->axis_y = HEIGHT / 2;
	i = -1;
	while (++i <= map->y)
		map->map[i] = (int **)malloc(sizeof(int *) * (map->x + 1));
	map->map[map->y] = NULL;
	map->next = NULL;
	return (map);
}

void	eb_map_init(t_map *map, char *str, int line)
{
	int		i;
	char	**tab;

	tab = ft_strsplit(str, ' ');
	i = -1;
	while (++i < map->x)
	{
		map->map[line][i] = (int *)ft_memalloc(sizeof(int));
		*(map->map[line][i]) = ft_atoi(tab[i]);
		if (*(map->map[line][i]) == map->start)
			eb_init_pos(i * RA + RA / 2, line * RA + RA / 2, map->pos);
	}
	map->map[line][map->x] = (int *)ft_memalloc(sizeof(int));
	map->map[line][map->x] = NULL;
}

t_map	*eb_map_add_to_queue(t_map *map, t_map *new_map)
{
	t_map	*tmp;

	if (map == NULL)
		map = new_map;
	else
	{
		tmp = map;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_map;
	}
	return map;
}
