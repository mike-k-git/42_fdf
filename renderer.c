/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:24:16 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:38 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_topleft_bottomright(t_data *d)
{
	int			x;
	int			y;
	t_point_2d	p;

	y = 0;
	while (y < d->map->props.height)
	{
		x = 0;
		while (x < d->map->props.width)
		{
			p = d->map->projected[y * d->map->props.width + x];
			if (p.x < d->map->props.top_x)
				d->map->props.top_x = p.x;
			if (p.x > d->map->props.bot_x)
				d->map->props.bot_x = p.x;
			if (p.y < d->map->props.top_y)
				d->map->props.top_y = p.y;
			if (p.y > d->map->props.bot_y)
				d->map->props.bot_y = p.y;
			x++;
		}
		y++;
	}
}

void	ft_set_offset(t_data *d)
{
	double	center_x;
	double	center_y;

	center_x = (double)(d->map->props.top_x + d->map->props.bot_x) / 2.0;
	center_y = (double)(d->map->props.top_y + d->map->props.bot_y) / 2.0;
	d->x_offset = (int)(WIDTH / 2 - center_x * d->scale);
	d->y_offset = (int)(HEIGHT / 2 - center_y * d->scale);
}

void	ft_set_scale(t_data *d)
{
	double	projected_width;
	double	projected_height;
	double	w_ratio;
	double	h_ratio;

	ft_set_topleft_bottomright(d);
	projected_width = d->map->props.bot_x - d->map->props.top_x;
	projected_height = d->map->props.bot_y - d->map->props.top_y;
	if (projected_width <= 0 || projected_height <= 0)
		d->scale = 1.0;
	else
	{
		w_ratio = (WIDTH * SCALE_RATIO) / projected_width;
		h_ratio = (HEIGHT * SCALE_RATIO) / projected_height;
		d->scale = fmin(w_ratio, h_ratio);
	}
	d->scale = ft_dclamp(d->scale, 0.1, 100.0);
}

void	ft_set_default_view(t_data *d)
{
	d->alpha = 0.0;
	d->beta = 0.0;
	d->gamma = 0.0;
	d->z_scale = 0.7;
	ft_set_trig(d);
	d->mouse = (t_mouse){0, -1, -1};
	ft_update_points(d);
	ft_set_scale(d);
	ft_set_offset(d);
}

void	ft_draw_map(t_data *d)
{
	int			x;
	int			y;
	t_point_2d	p;
	int			w;
	int			h;

	w = d->map->props.width;
	h = d->map->props.height;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			p = ft_project(d->map->projected[y * w + x], d);
			if (x + 1 < w)
				ft_line(p, ft_project(d->map->projected[y * w + x + 1], d), d);
			if (y + 1 < h)
				ft_line(p,
					ft_project(d->map->projected[(y + 1) * w + x], d), d);
			x++;
		}
		y++;
	}
}
