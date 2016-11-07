/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_zoom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:35:37 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 13:38:44 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom_map2(t_mlx *fdf, int keycode, t_param param)
{
	if (keycode == KEY_PG_UP)
	{
		param.zoom = 0;
		param.ratio = 1;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	if (keycode == KEY_PG_DOWN)
	{
		param.zoom = 0;
		param.ratio = -1;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
}

void		zoom_map(t_mlx *fdf, int keycode)
{
	t_param		param;

	param.x = 0;
	param.y = 0;
	param.reset = 0;
	clear_image(fdf->img);
	if (keycode == KEY_PLUS)
	{
		param.zoom = 1;
		param.ratio = 0;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	if (keycode == KEY_MINUS)
	{
		param.zoom = -1;
		param.ratio = 0;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	zoom_map2(fdf, keycode, param);
	draw_image(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	expose_hook(fdf);
}
