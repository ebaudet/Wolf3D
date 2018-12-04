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

typedef struct		s_colision
{
	int				face;
	double			dist;
}					t_colision;

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
	int				end;
	double			alpha;
	int				axis_y;
	int				***map;
	t_pos			*pos;
	struct s_map	*next;
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
	int				save[6];
	int				inter_colision;
	double			dist_screen;
	t_map			*map;
}					t_data;

typedef struct		s_line
{
	t_pos			*a;
	t_pos			*b;
}					t_line;

# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_RUN	65505


# define HEIGHT	850
# define WIDTH	1500
# define RA		100
# define VISION 60
# define DEG_TO_RAD 0.0174532925
# define MAXLEN	(d->map->x * d->map->y * RA)
# define RM		((HEIGHT / d->map->y) / 5)
# define RP		(RM / RA)
# define RUN	3

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
t_map	*eb_map_add_to_queue(t_map *map, t_map *new_map);

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
void	eb_clean_map(t_data *d);

/*
** eb_trace.c
*/
void	eb_trace_line(t_data *d, t_pos a, t_pos b, int color);
void	eb_trace_block(t_data *d, int x, int y);
void	eb_trace_map(t_data *d);

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
void	eb_search_wall(t_data *d, t_pos *pos, double alpha, t_colision *col);
void	eb_vision(t_data *d);
void	eb_print_wall(t_data *d, t_colision *col, int x);
void	eb_floor_casting(t_data *d, t_pos *pos, t_colision *col, double alpha);
void	eb_print_wend(t_data *d, double alpha, int dist, double dist_wall);

/*
**	eb_color.c
*/
int		color_shadow(int color, double shadow);
int		color_norm(int red, int green, int blue);

#endif /* WOLF3D_H */
