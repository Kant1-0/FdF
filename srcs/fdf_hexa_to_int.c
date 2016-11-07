/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hexa_to_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:34:20 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 17:35:24 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	hexa_to_int(char c)
{
	int		digit;

	if (c >= 'A' && c <= 'F')
		digit = (int)c - 55;
	else if (c >= 'a' && c <= 'f')
		digit = (int)c - 87;
	else
		digit = (int)c - 48;
	return (digit);
}

int			color_hexa(char *str)
{
	int		dig1;
	int		dig2;
	int		res;
	int		i;

	i = 0;
	dig2 = hexa_to_int(str[i]);
	++i;
	dig1 = hexa_to_int(str[i]);
	++i;
	res = (dig2 * pow(16, 1)) + (dig1 * pow(16, 0));
	return (res);
}
