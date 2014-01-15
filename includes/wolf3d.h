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

# include "../libft/includes/libft.h"

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;
typedef struct		s_map
{
	int				x;
	int				y;
	char			*name;
	int				wall;
	int				floor;
	int				start;
	double			alpha;
	int				***map;
	t_pos			*pos;
}					t_map;

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				x;
	int				y;
	int				width;
	int				height;
	t_map			*map;
}					t_data;

typedef struct		s_line
{
	t_pos			*a;
	t_pos			*b;
}					t_line;

# define HEIGHT	800
# define WIDTH	800
# define RA		100

/*
** eb_error.c
*/
int		eb_perror(char *str);

/*
** eb_getdata.c
*/
t_map	*eb_getdata(char *av[]);
t_map	*eb_init_t_map(t_map *map, char *str);
void	eb_map_init(t_map *map, char *str, int line);

/*
** eb_mlx.c
*/
void	eb_put_pixel_to_img(t_data *d, int x, int y, int color);
int		eb_expose_hook(t_data *d);
int		eb_mouse_hook(int button, int x, int y, t_data *d);
int		eb_key_hook(int keycode, t_data *d);
void	eb_mlx(t_data *d);

/*
** eb_draw.c
*/
void	eb_draw(t_data *d);
void	eb_clear_draw(t_data *d);

/*
** eb_trace.c
*/
void	eb_trace_line(t_data *d, t_pos a, t_pos b, int color);
void	eb_trace_block(t_data *d, int x, int y);

/*
** eb_init_struct.c
*/
void	eb_init_pos(int x, int y, t_pos *pos);
void	eb_init_line_pos(t_pos *a, t_pos *b, t_line *line);
t_line	*eb_init_line(int xa, int ya, int xb, int yb);

/*
** eb_tools.c
*/
void	eb_swap(int *a, int *b);
void	eb_swap_pos(t_pos *a, t_pos *b);
int		eb_abs(int x);

/*
** eb_move.c
*/
int		eb_collision(t_data *d, t_pos *pos);
void	eb_move_on(t_data *d);
void	eb_move_back(t_data *d);
void	eb_turn_right(t_data *d);
void	eb_turn_left(t_data *d);

/*
** eb_raytracing.c
*/
int		eb_search_wall(t_data *d, t_pos *pos, double alpha);
void	eb_vision(t_data *d);

#endif /* WOLF3D_H */
