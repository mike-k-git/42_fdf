/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:04:47 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:23 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_update_points(t_data *d)
{
	int				i;
	t_point			rot;
	t_projection	p;

	p = d->projection;
	i = 0;
	while (i < d->map->props.width * d->map->props.height)
	{
		rot = ft_rotate(d->map->original[i], d);
		if (p == PROJ_ISO)
			d->map->projected[i] = ft_project_iso(rot, d);
		else if (p == PROJ_TOP)
			d->map->projected[i] = ft_project_top_down(rot);
		else if (p == PROJ_SIDE)
			d->map->projected[i] = ft_project_side(rot, d);
		else if (p == PROJ_OBLIQUE_CAVALIER || p == PROJ_OBLIQUE_CABINET)
			d->map->projected[i] = ft_project_oblique(rot, d);
		i++;
	}
}

static void	ft_set_point(t_data *d, int y, int x, char **heights)
{
	int		z;
	int		idx;
	int		color;

	d->z_scale = 0.7;
	color = ft_get_color(heights[x]);
	idx = y * d->map->props.width + x;
	z = ft_atoi(heights[x]);
	d->map->original[idx].x = (double)x;
	d->map->original[idx].y = (double)y;
	d->map->original[idx].z = (double)z;
	d->map->original[idx].color = color;
	if (z < d->map->props.min)
		d->map->props.min = z;
	if (z > d->map->props.max)
		d->map->props.max = z;
}

static int	ft_process_line(t_data *d, int y, char *line)
{
	char	**heights;
	int		x;
	int		size;

	heights = ft_split(line, ' ', &size);
	if (heights == NULL)
		return (1);
	x = 0;
	while (x < d->map->props.width)
	{
		if (heights[x] == NULL)
		{
			ft_free_array(heights, size);
			return (1);
		}
		ft_set_point(d, y, x, heights);
		x++;
	}
	if (heights[x] != NULL)
	{
		ft_free_array(heights, size);
		return (1);
	}
	ft_free_array(heights, size);
	return (0);
}

int	ft_convert_to_points(t_data *d, t_list *raw_map)
{
	int		y;

	y = 0;
	while (y < d->map->props.height)
	{
		if (ft_process_line(d, y, raw_map->content))
			return (1);
		raw_map = raw_map->next;
		y++;
	}
	d->map->props.center_z = (d->map->props.max + d->map->props.min) / 2;
	return (0);
}
