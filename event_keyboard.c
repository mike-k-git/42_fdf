/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:58:50 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:32 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_reset(t_data *d)
{
	ft_set_default_view(d);
	ft_update_points(d);
	ft_render_image(d);
	return (0);
}

static int	ft_z_scale(int key, t_data *d)
{
	if (key == PLUS)
		d->z_scale += 0.05;
	else if (key == MINUS)
		d->z_scale -= 0.05;
	else if (key == SPACE)
		ft_set_default_view(d);
	d->z_scale = ft_dclamp(d->z_scale, 0.2, 1.0);
	ft_update_points(d);
	ft_render_image(d);
	return (0);
}

static int	ft_pan(int key, t_data *d)
{
	if (key == LEFT)
		d->x_offset -= WIDTH / 20;
	else if (key == RIGHT)
		d->x_offset += WIDTH / 20;
	else if (key == UP)
		d->y_offset -= HEIGHT / 20;
	else if (key == DOWN)
		d->y_offset += HEIGHT / 20;
	ft_render_image(d);
	return (0);
}

static int	ft_change_projection(t_data *d)
{
	d->projection = (d->projection + 1) % PROJ_COUNT;
	ft_reset_map_bounds(d);
	ft_set_default_view(d);
	ft_render_image(d);
	return (0);
}

int	ft_key_press(int key, t_data *d)
{
	if (key == ESCAPE)
		ft_clean_and_exit(d, NULL);
	else if (key == PLUS || key == MINUS)
		return (ft_z_scale(key, d));
	else if (key == SPACE)
		return (ft_reset(d));
	else if (key == LEFT || key == RIGHT || key == UP || key == DOWN)
		return (ft_pan(key, d));
	else if (key == RETURN)
		return (ft_change_projection(d));
	return (0);
}
