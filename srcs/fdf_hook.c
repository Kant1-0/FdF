/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:59:38 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 11:08:00 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		expose_hook(void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img->img_ptr, 0, 0);
	return (1);
}

int		key_hook(int keycode, void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		move_map(fdf, keycode);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS ||
		keycode == KEY_PG_UP || keycode == KEY_PG_DOWN)
		zoom_map(fdf, keycode);
	if (keycode == KEY_NUM_5)
		reset_map(fdf, keycode);
	if (keycode == KEY_ESC)
		mlx_exit(1, param, "");
	return (1);
}
