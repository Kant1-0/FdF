/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:57:49 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 16:59:27 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	new_color(unsigned char const b, unsigned char const g,
	unsigned char const r, unsigned char const a)
{
	t_color	new;

	new.rgba[0] = b;
	new.rgba[1] = g;
	new.rgba[2] = r;
	new.rgba[3] = a;
	return (new);
}

void	put_pixel_to_image(t_img const img, t_vert const vertex, t_mlx *fdf)
{
	if (vertex.pos.x < fdf->window_x && vertex.pos.y < fdf->window_y &&
		vertex.pos.x > 0 && vertex.pos.y > 0)
		ft_memcpy(img.data + vertex.pos.y * img.sizeline + vertex.pos.x *
			img.bpp / 8, &vertex.color, img.bpp / 8);
}
