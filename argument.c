/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:54:05 by mkugan            #+#    #+#             */
/*   Updated: 2025/07/13 22:41:10 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"

static void	usage(void)
{
	ft_printf("Usage: ./fdf <map_name>.fdf\n");
	exit(EXIT_SUCCESS);
}

static int	is_filename_valid(char *file)
{
	char	*last_dot;
	char	*last_slash;

	last_slash = ft_strrchr(file, '/');
	if (last_slash)
	{
		if (ft_strlen(last_slash + 1) < 5)
			return (0);
	}
	last_dot = ft_strrchr(file, '.');
	if (last_dot)
	{
		if (ft_strncmp(ft_strtolower(last_dot), ".fdf", 4) == 0)
			return (1);
	}
	return (0);
}

int	ft_parse_arguments(int argc, char **argv)
{
	int	fd;

	if (argc != 2 || !is_filename_valid(argv[1]))
		usage();
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
