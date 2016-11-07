/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:01:47 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 11:14:08 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	mlx_free(t_mlx *fdf)
{
	t_img		*img_curs;
	t_img		*img_temp;
	t_vert		*vert_curs;
	t_vert		*vert_temp;

	if (fdf->mlx_ptr && fdf->win_ptr)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	}
	img_curs = fdf->img;
	while (img_curs != NULL)
	{
		mlx_destroy_image(fdf->mlx_ptr, img_curs->img_ptr);
		img_temp = img_curs->next;
		free(img_curs);
		img_curs = img_temp;
	}
	vert_curs = fdf->map.vertex;
	while (vert_curs != NULL)
	{
		vert_temp = vert_curs->next;
		free(vert_curs);
		vert_curs = vert_temp;
	}
}

void		mlx_exit(int ret, t_mlx *fdf, char *error)
{
	if (ret < 1)
		ft_dprintf(2, "FDF Error - %s\n", error);
	if (ret == 1)
	{
		mlx_free(fdf);
	}
	exit(ret);
}
