/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:55:41 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 16:58:57 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			interpolate(double const a, double const b, double const f)
{
	return ((b - a) * f + a);
}

t_color			linear_interpolation(t_color const src, t_color const end,
	double const factor)
{
	return (new_color(
	interpolate(src.rgba[0], end.rgba[0], factor),
	interpolate(src.rgba[1], end.rgba[1], factor),
	interpolate(src.rgba[2], end.rgba[2], factor),
	interpolate(src.rgba[3], end.rgba[3], factor)));
}

double			norme(t_pos const a, t_pos const b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
