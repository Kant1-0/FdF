/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:38:25 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 21:36:52 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pos	delta_init(t_pos const start, t_pos const end)
{
	t_pos	delta;

	delta.x = (start.x - end.x >= 0 ? start.x - end.x : end.x - start.x);
	delta.y = (start.y - end.y >= 0 ? start.y - end.y : end.y - start.y);
	return (delta);
}

static t_pos	step_init(t_pos const start, t_pos const end)
{
	t_pos	step;

	step.x = (start.x < end.x ? 1 : -1);
	step.y = (start.y < end.y ? 1 : -1);
	return (step);
}

static void		update_pixel_pos(t_pos *current, t_pos const step,
	t_pos const delta, t_pos *error)
{
	if (error->y > -delta.x)
	{
		error->x -= delta.y;
		current->x += step.x;
	}
	if (error->y < delta.y)
	{
		error->x += delta.x;
		current->y += step.y;
	}
}

static double	distance(t_pos const target, t_pos const start, t_pos const end)
{
	return (norme(start, target) / norme(start, end));
}

void			draw_line(t_img const img, t_vert const start, t_vert const end,
	t_mlx *fdf)
{
	t_pos		delta;
	t_pos		step;
	t_pos		error;
	t_vert		curs;

	delta = delta_init(start.pos, end.pos);
	step = step_init(start.pos, end.pos);
	error.x = (delta.x > delta.y ? delta.x : -delta.y) / 2;
	curs = start;
	while (curs.pos.x != end.pos.x || curs.pos.y != end.pos.y)
	{
		put_pixel_to_image(img, curs, fdf);
		error.y = error.x;
		update_pixel_pos(&curs.pos, step, delta, &error);
		curs.color = linear_interpolation(start.color, end.color,
			distance(curs.pos, start.pos, end.pos));
	}
	put_pixel_to_image(img, curs, fdf);
}
