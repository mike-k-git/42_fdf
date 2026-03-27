/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:28:35 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:42 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Applies rotation in the order: X → Y → Z
// Around the center of the map (width/2, height/2)

static t_point	ft_rotate_x(t_point p, t_data *d)
{
	double	y;
	double	z;
	double	temp_y;
	double	temp_z;

	y = p.y;
	z = p.z;
	temp_y = y * d->cos_alpha - z * d->sin_alpha;
	temp_z = y * d->sin_alpha + z * d->cos_alpha;
	p.y = temp_y;
	p.z = temp_z;
	return (p);
}

static t_point	ft_rotate_y(t_point p, t_data *d)
{
	double	x;
	double	z;
	double	temp_x;
	double	temp_z;

	x = p.x;
	z = p.z;
	temp_x = x * d->cos_beta + z * d->sin_beta;
	temp_z = -x * d->sin_beta + z * d->cos_beta;
	p.x = temp_x;
	p.z = temp_z;
	return (p);
}

static t_point	ft_rotate_z(t_point p, t_data *d)
{
	double	x;
	double	y;
	double	new_x;
	double	new_y;

	x = p.x;
	y = p.y;
	new_x = x * d->cos_gamma - y * d->sin_gamma;
	new_y = x * d->sin_gamma + y * d->cos_gamma;
	p.x = new_x;
	p.y = new_y;
	return (p);
}

t_point	ft_rotate(t_point p, t_data *d)
{
	p.x = p.x - d->map->props.center_x;
	p.y = p.y - d->map->props.center_y;
	p.z = p.z - d->map->props.center_z;
	p = ft_rotate_x(p, d);
	p = ft_rotate_y(p, d);
	p = ft_rotate_z(p, d);
	p.x = p.x + d->map->props.center_x;
	p.y = p.y + d->map->props.center_y;
	p.z = p.z + d->map->props.center_z;
	return (p);
}
