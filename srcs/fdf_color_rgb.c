/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 13:58:08 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 17:00:38 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color		create_color_rgb(int rgb)
{
	t_color		color;

	color.rgba[0] = 200 - (rgb * 20);
	color.rgba[1] = 200 - (rgb * 20);
	color.rgba[2] = 0 + (rgb * 20);
	color.rgba[3] = 0;
	return (color);
}
