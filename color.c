/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:28:59 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:20 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_color(char *s)
{
	int		color;
	char	*comma;

	comma = ft_strchr(s, ',');
	if (comma)
	{
		color = (int)ft_atol(comma + 1, NULL, 16);
		if (color == 0)
			return (0xFFFFFFFF);
		if (color < 0xFF)
			color = (color << 16) | (color << 8) | color;
		else if (color <= 0xFFF)
			color = (((color >> 8) & 0xF) * 17) << 16
				| (((color >> 4) & 0xF) * 17) << 8
				| ((color & 0xF) * 17);
		color |= 0xFF000000;
		return (color);
	}
	return (0xFFFFFFFF);
}

// linear interpolation between 'c1' and 'c2' based on 't'
// t = 0.0 -> full c1
// t = 1.0 -> full c2
// t = 0.5 -> 50% blend

int	ft_blend_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	t = ft_fclamp(t, 0.0f, 1.0f);
	r = (int)((1.0f - t) * ((c1 >> 16) & 0xFF) + t * ((c2 >> 16) & 0xFF));
	g = (int)((1.0f - t) * ((c1 >> 8) & 0xFF) + t * ((c2 >> 8) & 0xFF));
	b = (int)((1.0f - t) * (c1 & 0xFF) + t * (c2 & 0xFF));
	r = ft_iclamp(r, 0, 255);
	g = ft_iclamp(g, 0, 255);
	b = ft_iclamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}
