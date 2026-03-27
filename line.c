/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:52:20 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:47 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap_2d(t_point_2d *a, t_point_2d *b)
{
	int	tmp;

	ft_swap(&a->x, &b->x, sizeof(double));
	ft_swap(&a->y, &b->y, sizeof(double));
	tmp = a->color;
	a->color = b->color;
	b->color = tmp;
}

void	ft_draw_line(t_line l, t_point_2d p1, t_point_2d p2, t_data *d)
{
	int		y;
	int		x;

	y = p1.y;
	x = p1.x;
	while (x <= p2.x)
	{
		if (l.dx == 0)
			l.t = (float)(y - p1.y) / l.dy;
		else
			l.t = (float)(x - p1.x) / l.dx;
		l.color = ft_blend_color(p1.color, p2.color, l.t);
		if (l.steep)
			ft_put_pixel(&d->img, y, x, l.color);
		else
			ft_put_pixel(&d->img, x, y, l.color);
		l.err -= l.dy;
		if (l.err < 0)
		{
			y += l.ystep;
			l.err += l.dx;
		}
		x++;
	}
}

void	ft_line(t_point_2d p1, t_point_2d p2, t_data *d)
{
	t_line	l;

	ft_memset(&l, 0, sizeof(t_line));
	if (fabs(p2.y - p1.y) > fabs(p2.x - p1.x))
		l.steep = 1;
	else
		l.steep = 0;
	if (l.steep)
	{
		ft_swap(&p1.x, &p1.y, sizeof(double));
		ft_swap(&p2.x, &p2.y, sizeof(double));
	}
	if (p1.x > p2.x)
		ft_swap_2d(&p1, &p2);
	l.dx = p2.x - p1.x;
	l.dy = fabs(p2.y - p1.y);
	l.err = l.dx / 2;
	if (p1.y < p2.y)
		l.ystep = 1;
	else
		l.ystep = -1;
	ft_draw_line(l, p1, p2, d);
}
