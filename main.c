/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:44:49 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:58 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	ft_parse_map(&data, ft_parse_arguments(argc, argv));
	ft_mlx_init(&data, argv[1]);
	ft_set_default_view(&data);
	ft_render_image(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
