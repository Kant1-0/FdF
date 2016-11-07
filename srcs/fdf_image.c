/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:50:36 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 14:30:30 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_img *img)
{
	ft_bzero(img->data, img->width * img->height * img->bpp / 8);
}

void	draw_image(t_mlx *fdf)
{
	t_vert		*start;
	int			redraw;

	redraw = 1;
	start = fdf->map.vertex;
	if (start->next == NULL)
		draw_rectangle(fdf, *start, *start, &redraw);
	else
	{
		while (start != NULL)
		{
			if (start->next)
				draw_rectangle(fdf, *start, *(start->next), &redraw);
			start = start->next;
		}
	}
}
