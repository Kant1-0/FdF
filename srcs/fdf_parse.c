/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 16:01:39 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 15:17:12 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}

static void	compute_tiling(t_map *map, t_mlx *fdf)
{
	int		tile;

	if (fdf->map.length < fdf->map.height)
		tile = fdf->map.height;
	else
		tile = fdf->map.length;
	if (fdf->window_x > fdf->window_y)
	{
		map->tile_x = (fdf->window_x / (tile * 2));
		map->tile_y = (fdf->window_x / (tile * 2));
	}
	if (fdf->window_x < fdf->window_y)
	{
		map->tile_x = (fdf->window_y / (tile * 2));
		map->tile_y = (fdf->window_y / (tile * 2));
	}
}

static void	parse_line(t_vert **vertex, t_parse pars, t_mlx *fdf)
{
	int			i;
	char		*digit;
	char		*hexa;
	char		**tab;

	i = 0;
	tab = ft_strsplit(pars.line, ' ');
	digit = NULL;
	while (i < fdf->map.length)
	{
		ft_memchr_cpy(&digit, tab[i], ',');
		hexa = ft_strchr(tab[i], 'x');
		if (((pars.z = ft_atoi(digit)) < -2147483648) || pars.z > 2147483647)
			mlx_exit(-1, fdf, "parse_line, a given int will overflow");
		if (hexa == NULL)
			*vertex = lst_vert_new_rgb(vertex, pars, fdf);
		else
			*vertex = lst_vert_new_hex(vertex, pars, fdf, hexa);
		pars.x += fdf->map.tile_x;
		++i;
	}
	if (digit)
		free(digit);
	free_tab(tab);
}

void		init_map(t_mlx *fdf)
{
	t_parse		pars;

	compute_tiling(&fdf->map, fdf);
	pars.fd = open(fdf->map.file, O_RDONLY);
	if (pars.fd == -1)
		mlx_exit(-1, fdf, "init_map, can't open file");
	pars.x = 0;
	pars.y = 0;
	pars.i = 1;
	fdf->map.vertex = NULL;
	while (get_next_line(pars.fd, &pars.line))
	{
		ft_printf("PARSING LINE %4d OUT OF %4d\r", pars.i++, fdf->map.height);
		parse_line(&(fdf->map.vertex), pars, fdf);
		pars.y += fdf->map.tile_y;
		free(pars.line);
	}
	close(pars.fd);
}
