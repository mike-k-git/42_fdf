/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:30:02 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/09 20:27:52 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>

# define WIDTH					1360
# define HEIGHT					768
# define INFO_HEIGHT			50

# define SCALE_RATIO			0.7
# define ISO_ANGLE_COS			0.86602540378
# define ISO_ANGLE_SIN			0.49999999999
# define CAVALIER_ANGLE			0.5
# define CABINET_ANGLE			1.0

# define ROTATE_SPEED			0.02

# define ESCAPE					0xff1b
# define LEFT					0xff51
# define UP						0xff52
# define RIGHT					0xff53
# define DOWN					0xff54
# define SPACE					0x0020
# define PLUS					0x0031
# define MINUS					0x0032
# define RETURN					0xff0d

# define MOUSE_LEFT				1
# define MOUSE_SCROLL_DOWN		4
# define MOUSE_SCROLL_UP		5

# define KEY_PRESS				2
# define BUTTON_PRESS			4
# define BUTTON_RELEASE			5
# define MOTION_NOTIFY			6
# define DESTROY_NOTIFY			17

# define KEY_PRESS_MASK			0x1L
# define BUTTON_PRESS_MASK		0x4L
# define BUTTON_RELEASE_MASK	0x8L
# define MOTION_NOTIFY_MASK		0x40L
# define STRUCTURE_NOTIFY_MASK	0x20000L

# define PROJ_COUNT				5

# define FDF_DBL_MAX			1.7976931348623157E+308

typedef enum e_projection
{
	PROJ_ISO,
	PROJ_TOP,
	PROJ_SIDE,
	PROJ_OBLIQUE_CAVALIER,
	PROJ_OBLIQUE_CABINET
}	t_projection;

typedef struct s_point_2d
{
	double	x;
	double	y;
	int		color;
}	t_point_2d;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_map_props
{
	int		height;
	int		width;
	int		max;
	int		min;
	double	top_x;
	double	top_y;
	double	bot_x;
	double	bot_y;
	int		center_x;
	int		center_y;
	int		center_z;
}	t_map_props;

typedef struct s_map
{
	t_point		*original;
	t_point_2d	*projected;
	t_map_props	props;
}	t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mouse
{
	int	drag;
	int	x;
	int	y;
}	t_mouse;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_map			*map;
	t_mouse			mouse;
	double			scale;
	double			z_scale;
	double			alpha;
	double			beta;
	double			gamma;
	double			sin_alpha;
	double			cos_alpha;
	double			sin_beta;
	double			cos_beta;
	double			sin_gamma;
	double			cos_gamma;
	int				x_offset;
	int				y_offset;
	t_projection	projection;
}	t_data;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		steep;
	int		err;
	int		ystep;
	float	t;
	int		color;
}	t_line;

int			ft_parse_arguments(int argc, char **argv);
int			ft_key_press(int key, t_data *d);
void		ft_clean_and_exit(t_data *d, const char *err);
void		ft_mlx_init(t_data *d, char *title);
void		ft_parse_map(t_data *d, int fd);
void		ft_render_image(t_data *d);
void		ft_put_pixel(t_img *i, int x, int y, int color);
void		ft_draw_map(t_data *d);
void		ft_set_default_view(t_data *d);
void		ft_map_err(t_data *d, t_list *rm, char *err, int fd);
int			ft_convert_to_points(t_data *d, t_list *raw_map);
void		ft_line(t_point_2d p1, t_point_2d p2, t_data *d);
int			ft_mouse_hook(int button, int x, int y, t_data *d);
void		ft_set_offset(t_data *d);
void		ft_set_scale(t_data *d);
t_point		ft_rotate(t_point p, t_data *d);
int			ft_mouse_down(int button, int x, int y, t_data *d);
int			ft_mouse_up(int button, int x, int y, t_data *d);
int			ft_mouse_move(int x, int y, t_data *d);
void		ft_update_iso_points(t_data *d);
int			ft_get_color(char *point);
int			ft_blend_color(int c1, int c2, float t);
float		ft_fclamp(float var, float min, float max);
int			ft_iclamp(int var, int min, int max);
double		ft_dclamp(double var, double min, double max);
t_point_2d	ft_project_iso(t_point p, t_data *d);
void		ft_set_trig(t_data *d);
t_point_2d	ft_project_top_down(t_point p);
void		ft_update_points(t_data *d);
t_point_2d	ft_project_side(t_point p, t_data *d);
t_point_2d	ft_project_oblique(t_point p, t_data *d);
void		ft_reset_map_bounds(t_data *d);
t_point_2d	ft_project(t_point_2d p, t_data *d);
void		ft_draw_info(t_data *d);

#endif
