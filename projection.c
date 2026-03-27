/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:28:24 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:30 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point_2d	ft_project(t_point_2d p, t_data *d)
{
	t_point_2d	v;

	v.x = p.x * d->scale + d->x_offset;
	v.y = p.y * d->scale + d->y_offset;
	v.color = p.color;
	return (v);
}

t_point_2d	ft_project_iso(t_point p, t_data *d)
{
	t_point_2d	iso;

	iso.x = (p.x - p.y) * ISO_ANGLE_COS;
	iso.y = (p.x + p.y) * ISO_ANGLE_SIN - p.z * d->z_scale;
	iso.color = p.color;
	return (iso);
}

t_point_2d	ft_project_top_down(t_point p)
{
	t_point_2d	td;

	td.x = p.x;
	td.y = p.y;
	td.color = p.color;
	return (td);
}

t_point_2d	ft_project_side(t_point p, t_data *d)
{
	t_point_2d	side;

	side.x = p.x;
	side.y = -p.z * d->z_scale;
	side.color = p.color;
	return (side);
}

t_point_2d	ft_project_oblique(t_point p, t_data *d)
{
	t_point_2d	oblique;
	double		angle;

	angle = 1.0;
	if (d->projection == PROJ_OBLIQUE_CAVALIER)
		angle = CAVALIER_ANGLE;
	else if (d->projection == PROJ_OBLIQUE_CABINET)
		angle = CABINET_ANGLE;
	oblique.x = p.x + angle * p.z * d->z_scale;
	oblique.y = p.y + angle * p.z * d->z_scale;
	oblique.color = p.color;
	return (oblique);
}
