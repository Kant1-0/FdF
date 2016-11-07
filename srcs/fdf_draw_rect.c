/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:48:04 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 11:01:08 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	is_reset_param(int *redraw, int *x, int *y)
{
	if (*redraw == 1)
	{
		*x = 1;
		*y = 1;
		*redraw = 0;
	}
}

static void	init_side_rectangle(t_vert **left, t_vert **right, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		if ((*left)->next)
			*left = (*left)->next;
		if ((*right)->next)
			*right = (*right)->next;
		++i;
	}
}

static void	draw_rect_and_diagonal(t_mlx *fdf, t_vert start, t_vert end)
{
	t_vert		*left;
	t_vert		*right;

	left = &start;
	right = &end;
	init_side_rectangle(&left, &right, fdf->map.length);
	draw_line(*(fdf->img), start, end, fdf);
	draw_line(*(fdf->img), start, *left, fdf);
	if (((start.pos.z > left->pos.z) && (start.pos.z > end.pos.z)) ||
		((right->pos.z > left->pos.z) && (right->pos.z > end.pos.z)) ||
		((start.pos.z < left->pos.z) && (start.pos.z < end.pos.z)) ||
		((right->pos.z < left->pos.z) && (right->pos.z < end.pos.z)))
		draw_line(*(fdf->img), *left, end, fdf);
	else if (((end.pos.z > right->pos.z) && (end.pos.z > start.pos.z)) ||
		((left->pos.z > right->pos.z) && (left->pos.z > start.pos.z)) ||
		((end.pos.z < right->pos.z) && (end.pos.z < start.pos.z)) ||
		((left->pos.z < right->pos.z) && (left->pos.z < start.pos.z)))
		draw_line(*(fdf->img), start, *right, fdf);
}

static void	draw_last_xline(t_mlx *fdf, t_vert start, t_vert end)
{
	t_vert		*left;
	t_vert		*right;

	left = &start;
	right = &end;
	init_side_rectangle(&left, &right, fdf->map.length);
	draw_line(*(fdf->img), start, *left, fdf);
}

void		draw_rectangle(t_mlx *fdf, t_vert start, t_vert end, int *redraw)
{
	static int	x = 1;
	static int	y = 1;

	is_reset_param(redraw, &x, &y);
	if (x == fdf->map.length)
	{
		draw_last_xline(fdf, start, end);
		x = 1;
		++y;
	}
	else if (y == fdf->map.height)
	{
		draw_line(*(fdf->img), start, end, fdf);
		++x;
	}
	else
	{
		draw_rect_and_diagonal(fdf, start, end);
		++x;
	}
}
