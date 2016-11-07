/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:45:59 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 13:16:26 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_coord(t_vert **new, t_parse p, t_mlx *fdf)
{
	(*new)->pos.x = ((p.x - p.y) * (TILE_HALF)) + (fdf->window_x /
		fdf->ratio_x);
	(*new)->pos.y = (((p.x * 0.5 + p.y * 0.5) * (TILE_HALF)) +
		(fdf->window_y / fdf->ratio_y)) - (p.z * EXPONENT_Z);
	(*new)->pos.z = p.z;
	(*new)->pos.coord[0] = p.x;
	(*new)->pos.coord[1] = p.y;
	(*new)->pos.coord[2] = p.z;
}

t_vert		*lst_vert_new_rgb(t_vert **vertex, t_parse p, t_mlx *fdf)
{
	t_vert		*new;
	t_vert		*curs;

	new = NULL;
	new = (t_vert*)malloc(sizeof(t_vert));
	if (new == NULL)
		return (NULL);
	add_coord(&new, p, fdf);
	new->color = create_color_rgb(p.z);
	new->next = NULL;
	if (*vertex == NULL)
		return (new);
	else
	{
		curs = *vertex;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*vertex);
}

t_vert		*lst_vert_new_hex(t_vert **vertex, t_parse p, t_mlx *fdf,
	char *hexa)
{
	t_vert		*new;
	t_vert		*curs;

	new = NULL;
	new = (t_vert*)malloc(sizeof(t_vert));
	if (new == NULL)
		return (NULL);
	add_coord(&new, p, fdf);
	ft_printf("");
	new->color = create_color_hex(hexa);
	new->next = NULL;
	if (*vertex == NULL)
		return (new);
	else
	{
		curs = *vertex;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*vertex);
}

t_img		*lst_img_new(t_img **img, int width, int height)
{
	t_img		*new;
	t_img		*curs;

	new = NULL;
	new = (t_img*)malloc(sizeof(t_img));
	if (new == NULL)
		return (NULL);
	new->width = width;
	new->height = height;
	new->next = NULL;
	if (*img == NULL)
		return (new);
	else
	{
		curs = *img;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*img);
}
