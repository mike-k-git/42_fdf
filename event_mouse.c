/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:41:36 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:37 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_down(int button, int x, int y, t_data *d)
{
	double	old_scale;

	old_scale = d->scale;
	if (button == MOUSE_LEFT)
		d->mouse.drag = 1;
	d->mouse.x = x;
	d->mouse.y = y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		if (button == MOUSE_SCROLL_UP)
			d->scale *= 1.1;
		else if (button == MOUSE_SCROLL_DOWN)
			d->scale /= 1.1;
		if (d->scale < 0.1 || d->scale > 100.0)
		{
			d->scale = ft_dclamp(d->scale, 0.1, 100.0);
			return (0);
		}
		d->x_offset = x - (x - d->x_offset) / old_scale * d->scale;
		d->y_offset = y - (y - d->y_offset) / old_scale * d->scale;
		ft_render_image(d);
	}
	return (0);
}

int	ft_mouse_up(int button, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		d->mouse.drag = 0;
	return (0);
}

static void	ft_normalize_angles(t_data *d)
{
	double	two_pi;

	two_pi = 2.0 * M_PI;
	d->alpha = fmod(d->alpha, two_pi);
	if (d->alpha < 0)
		d->alpha += two_pi;
	d->beta = fmod(d->beta, two_pi);
	if (d->beta < 0)
		d->beta += two_pi;
	d->gamma = fmod(d->gamma, two_pi);
	if (d->gamma < 0)
		d->gamma += two_pi;
}

int	ft_mouse_move(int x, int y, t_data *d)
{
	if (d->mouse.drag)
	{
		d->beta += (double)(x - d->mouse.x) * ROTATE_SPEED;
		d->alpha += (double)(y - d->mouse.y) * ROTATE_SPEED;
		ft_normalize_angles(d);
		ft_set_trig(d);
		ft_update_points(d);
		ft_render_image(d);
		d->mouse.x = x;
		d->mouse.y = y;
	}
	return (0);
}
