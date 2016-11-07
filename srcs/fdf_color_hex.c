/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 13:58:08 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 13:07:59 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_hex_1(char *hexa, t_color *color, char *str, int *i)
{
	int		j;

	j = 0;
	while (j < 2)
	{
		str[j] = hexa[*i];
		++(*i);
		++j;
	}
	color->rgba[2] = color_hexa(str);
}

static int	compute_hex_2(char *hexa, t_color *color, char *str, int *i)
{
	int		j;

	j = 0;
	while (j < 2)
	{
		if (hexa[*i] == ' ' || hexa[*i] == '\0' || hexa[*i] == '\n')
		{
			color->rgba[0] = color->rgba[2];
			color->rgba[1] = 0;
			color->rgba[2] = 0;
			return (1);
		}
		else
		{
			str[j] = hexa[*i];
			++(*i);
		}
		++j;
	}
	color->rgba[1] = color_hexa(str);
	return (0);
}

static int	compute_hex_3(char *hexa, t_color *color, char *str, int *i)
{
	int		j;

	j = 0;
	while (j < 2)
	{
		if (hexa[*i] == ' ' || hexa[*i] == '\0' || hexa[*i] == '\n')
		{
			color->rgba[0] = color->rgba[1];
			color->rgba[1] = color->rgba[2];
			color->rgba[2] = 0;
			return (1);
		}
		else
		{
			str[j] = hexa[*i];
			++(*i);
		}
		++j;
	}
	color->rgba[0] = color_hexa(str);
	return (0);
}

t_color		create_color_hex(char *hexa)
{
	t_color		color;
	char		*str;
	int			i;
	int			j;

	i = 1;
	j = 0;
	str = ft_memalloc(3);
	compute_hex_1(hexa, &color, str, &i);
	if (compute_hex_2(hexa, &color, str, &i) == 1)
	{
		free(str);
		return (color);
	}
	if (compute_hex_3(hexa, &color, str, &i) == 1)
	{
		free(str);
		return (color);
	}
	color.rgba[3] = 0;
	free(str);
	return (color);
}
