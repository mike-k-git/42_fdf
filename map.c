/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:21:46 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:42:15 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include <unistd.h>

void	ft_reset_map_bounds(t_data *d)
{
	d->map->props.top_x = FDF_DBL_MAX;
	d->map->props.top_y = FDF_DBL_MAX;
	d->map->props.bot_x = -FDF_DBL_MAX;
	d->map->props.bot_y = -FDF_DBL_MAX;
}

static void	ft_init_map(t_data *d, int fd)
{
	d->map = malloc(sizeof(t_map));
	if (!d->map)
		ft_map_err(d, NULL, "Map initialization error.\n", fd);
	d->map->props = (t_map_props){
		.height = 0,
		.width = 0,
		.max = INT_MIN,
		.min = INT_MAX,
		.top_x = FDF_DBL_MAX,
		.top_y = FDF_DBL_MAX,
		.bot_x = -FDF_DBL_MAX,
		.bot_y = -FDF_DBL_MAX,
		.center_x = 0,
		.center_y = 0,
		.center_z = 0};
	d->map->original = NULL;
	d->map->projected = NULL;
}

static void	*ft_read_raw_map(t_data *d, int fd)
{
	char	*next_line;
	char	*trimmed_line;
	t_list	*node;
	t_list	*rm;

	rm = NULL;
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		trimmed_line = ft_strtrim(next_line, " \n\r\t\v\f");
		free(next_line);
		if (!trimmed_line)
			ft_map_err(d, rm, "Line trimming error.\n", fd);
		node = ft_lstnew(trimmed_line);
		if (!node)
			ft_map_err(d, rm, "Raw map node allocation error.\n", fd);
		ft_lstadd_back(&rm, node);
	}
	return (rm);
}

static int	ft_set_map_size(t_data *d, t_list *raw_map)
{
	char	**first_line_split;
	int		size;

	first_line_split = ft_split(raw_map->content, ' ', &size);
	if (!first_line_split)
		return (1);
	ft_free_array(first_line_split, size);
	if (size == 0)
		return (1);
	d->map->props.width = size;
	d->map->props.center_x = d->map->props.width / 2;
	d->map->props.height = ft_lstsize(raw_map);
	d->map->props.center_y = d->map->props.height / 2;
	return (0);
}

void	ft_parse_map(t_data *d, int fd)
{
	t_list	*raw_map;
	int		n_points;

	ft_init_map(d, fd);
	raw_map = ft_read_raw_map(d, fd);
	if (raw_map == NULL)
		ft_map_err(d, raw_map, "Raw map is empty.\n", fd);
	if (ft_set_map_size(d, raw_map))
		ft_map_err(d, raw_map, "Map's size cannot be initialized.\n", fd);
	n_points = d->map->props.width * d->map->props.height;
	d->map->original = malloc(sizeof(t_point) * n_points);
	d->map->projected = malloc(sizeof(t_point_2d) * n_points);
	if (d->map->original == NULL || d->map->projected == NULL)
		ft_map_err(d, raw_map, "Points allocation error.\n", fd);
	if (ft_convert_to_points(d, raw_map))
		ft_map_err(d, raw_map, "Points conversion error.\n", fd);
	close(fd);
	ft_lstclear(&raw_map, free);
}
