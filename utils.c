/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:28:41 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:48 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_fclamp(float var, float min, float max)
{
	if (var > max)
		return (max);
	if (var < min)
		return (min);
	return (var);
}

int	ft_iclamp(int var, int min, int max)
{
	if (var > max)
		return (max);
	if (var < min)
		return (min);
	return (var);
}

double	ft_dclamp(double var, double min, double max)
{
	if (var > max)
		return (max);
	if (var < min)
		return (min);
	return (var);
}

void	ft_set_trig(t_data *d)
{
	d->sin_alpha = sin(d->alpha);
	d->cos_alpha = cos(d->alpha);
	d->sin_beta = sin(d->beta);
	d->cos_beta = cos(d->beta);
	d->sin_gamma = sin(d->gamma);
	d->cos_gamma = cos(d->gamma);
}
