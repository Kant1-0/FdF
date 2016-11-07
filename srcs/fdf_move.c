/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:09:03 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 13:42:03 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_param(t_param param, t_mov *mov)
{
	if (param.reset == 1)
	{
		mov->exp = 4;
		mov->tile = TILE_HALF;
		mov->mov_x = 0;
		mov->mov_y = 0;
		return ;
	}
	if (param.zoom == 1)
		mov->tile += 0.10;
	else if (param.zoom == -1)
		mov->tile -= 0.10;
	if (param.ratio == 1)
		mov->exp += 0.5;
	else if (param.ratio == -1)
		mov->exp -= 0.5;
	mov->mov_x += param.x;
	mov->mov_y += param.y;
}

static void	move_map2(t_mlx *fdf, int keycode, t_param param)
{
	if (keycode == KEY_UP)
	{
		param.x = 0;
		param.y = 10;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	if (keycode == KEY_DOWN)
	{
		param.x = 0;
		param.y = -10;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
}

void		move_map(t_mlx *fdf, int keycode)
{
	t_param		param;

	param.zoom = 0;
	param.ratio = 0;
	param.reset = 0;
	clear_image(fdf->img);
	if (keycode == KEY_LEFT)
	{
		param.x = 10;
		param.y = 0;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	if (keycode == KEY_RIGHT)
	{
		param.x = -10;
		param.y = 0;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	move_map2(fdf, keycode, param);
	draw_image(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	expose_hook(fdf);
}

void		reset_map(t_mlx *fdf, int keycode)
{
	t_param		param;

	param.zoom = 0;
	param.ratio = 0;
	param.x = 0;
	param.y = 0;
	clear_image(fdf->img);
	if (keycode == KEY_NUM_5)
	{
		param.reset = 1;
		move_vertex(&(fdf->map.vertex), param, fdf);
	}
	draw_image(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	expose_hook(fdf);
}

void		move_vertex(t_vert **start, t_param param, t_mlx *fdf)
{
	t_vert			*curs;

	init_param(param, &(fdf->mov));
	curs = *start;
	while (curs != NULL)
	{
		curs->pos.x = (((curs->pos.coord[0] - curs->pos.coord[1]) *
			fdf->mov.tile) + (fdf->window_x / fdf->ratio_x)) + fdf->mov.mov_x;
		curs->pos.y = (((curs->pos.coord[0] + curs->pos.coord[1]) *
			(fdf->mov.tile * 0.5)) + (fdf->window_y / fdf->ratio_y) -
			(curs->pos.z * fdf->mov.exp)) + fdf->mov.mov_y;
		curs = curs->next;
	}
}
