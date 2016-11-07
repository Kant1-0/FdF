/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:40:50 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 13:59:04 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_window(t_mlx *fdf)
{
	float	ratio;

	ratio = (float)fdf->map.length / (float)fdf->map.height;
	if (ratio >= 1.3)
	{
		fdf->window_x = WINDOW_X * 1.8;
		fdf->window_y = WINDOW_Y * 1.8;
		fdf->ratio_x = 2.5;
		fdf->ratio_y = fdf->tall;
	}
	else if (ratio <= 0.7 || fdf->tall >= 3)
	{
		fdf->window_x = WINDOW_X * 1.8;
		fdf->window_y = WINDOW_TL * 1.8;
		fdf->ratio_x = 2;
		fdf->ratio_y = fdf->tall;
	}
	else
	{
		fdf->window_x = WINDOW_X * 1.8;
		fdf->window_y = WINDOW_EQ * 1.8;
		fdf->ratio_x = 2;
		fdf->ratio_y = fdf->tall;
	}
}

static void	init_mov_param(t_mov *mov)
{
	mov->tile = TILE_HALF;
	mov->exp = EXPONENT_Z;
	mov->mov_x = 0;
	mov->mov_y = 0;
}

void		init_fdf(t_mlx *fdf)
{
	char	*str;
	int		size;

	size = ft_strlen(API_NAME) + ft_strlen(fdf->map.file);
	str = (char*)ft_memalloc(size);
	ft_strcat(str, API_NAME);
	ft_strcat(str, fdf->map.file);
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_init failed");
	compute_window(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->window_x,
		fdf->window_y, str);
	if (fdf->win_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_new_window failed");
	fdf->img = NULL;
	fdf->img = lst_img_new(&fdf->img, fdf->window_x, fdf->window_y);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img->width,
		fdf->img->height);
	if (fdf->img->img_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_new_image failed");
	fdf->img->data = mlx_get_data_addr(fdf->img->img_ptr, &(fdf->img->bpp),
		&(fdf->img->sizeline), &(fdf->img->endian));
}

int			main(int ac, char **av)
{
	t_mlx		fdf;

	if (ac == 2)
	{
		error_map(&fdf, av[1]);
		init_fdf(&fdf);
		init_map(&fdf);
		init_mov_param(&(fdf.mov));
		draw_image(&fdf);
		mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
		mlx_expose_hook(fdf.win_ptr, expose_hook, &fdf);
		mlx_loop(fdf.mlx_ptr);
	}
	else
		ft_printf("FDF Error - enter a file to parse\n");
	return (0);
}
