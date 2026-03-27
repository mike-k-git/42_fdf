/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:58:06 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:27 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include <unistd.h>

void	ft_map_err(t_data *d, t_list *rm, char *err, int fd)
{
	if (fd >= 0)
		close(fd);
	if (rm != NULL)
		ft_lstclear(&rm, free);
	if (d->map && d->map->original)
		free(d->map->original);
	if (d->map && d->map->projected)
		free(d->map->projected);
	if (d->map)
		free(d->map);
	ft_dprintf(2, err);
	exit(EXIT_FAILURE);
}

void	ft_clean_and_exit(t_data *data, const char *err)
{
	if (data->mlx_ptr)
	{
		if (data->img.img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free(data->map->original);
	free(data->map->projected);
	free(data->map);
	if (err != NULL)
	{
		perror(err);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
