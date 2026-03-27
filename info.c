/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:41:41 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:42 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_info(t_data *d)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, 20, HEIGHT - 50,
		0x00FFFF, "+/-: Increase/Decrease Elevation | Arrows: Pan");
	mlx_string_put(d->mlx_ptr, d->win_ptr, 20, HEIGHT - 35,
		0x00FFFF, "Return: Next Projection | SPACE: Reset view | ESC: exit");
	mlx_string_put(d->mlx_ptr, d->win_ptr, 20, HEIGHT - 20,
		0x00FFFF, "Mouse Click and Drag: Rotate along X and Y axes");
}
