/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:57:43 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:19 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_destroy(t_data *data)
{
	ft_clean_and_exit(data, NULL);
	return (0);
}

static void	ft_image_init(t_data *d)
{
	d->img.img_ptr = mlx_new_image(d->mlx_ptr, WIDTH, HEIGHT);
	if (!d->img.img_ptr)
		ft_clean_and_exit(d, "mlx_new_image");
	d->img.addr = mlx_get_data_addr(d->img.img_ptr,
			&d->img.bpp, &d->img.line_length, &d->img.endian);
	if (!d->img.addr)
		ft_clean_and_exit(d, "mlx_get_data_addr");
}

void	ft_put_pixel(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = i->addr + (y * i->line_length + x * (i->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_render_image(t_data *d)
{
	ft_memset(d->img.addr, 0, HEIGHT * d->img.line_length);
	ft_draw_map(d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.img_ptr, 0, 0);
	ft_draw_info(d);
}

void	ft_mlx_init(t_data *d, char *title)
{
	d->mlx_ptr = mlx_init();
	if (d->mlx_ptr == NULL)
		ft_clean_and_exit(d, "mlx_init");
	d->win_ptr = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, title);
	if (d->win_ptr == NULL)
		ft_clean_and_exit(d, "mlx_new_window");
	mlx_hook(d->win_ptr, KEY_PRESS, KEY_PRESS_MASK, ft_key_press, d);
	mlx_hook(d->win_ptr, BUTTON_PRESS, BUTTON_PRESS_MASK, ft_mouse_down, d);
	mlx_hook(d->win_ptr, BUTTON_RELEASE, BUTTON_RELEASE_MASK, ft_mouse_up, d);
	mlx_hook(d->win_ptr, MOTION_NOTIFY, MOTION_NOTIFY_MASK, ft_mouse_move, d);
	mlx_hook(d->win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, ft_destroy, d);
	ft_image_init(d);
}
