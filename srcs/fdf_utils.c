/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:47:07 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/01 17:01:13 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_strichr(const char *str, int c)
{
	char	*ptr_str;
	int		i;

	if (!str)
		return (0);
	ptr_str = (char *)str;
	i = 0;
	while (*ptr_str != c)
	{
		if (*ptr_str == '\0')
			return (ft_strlen(str));
		ptr_str++;
		++i;
	}
	return (i);
}

char		*ft_memchr_cpy(char **dst, const char *src, int endchr)
{
	size_t		i;

	i = ft_strichr(src, endchr);
	if (*dst)
		free(*dst);
	*dst = (char*)ft_memalloc(i + 1);
	ft_strncpy(*dst, src, i);
	return (*dst);
}

char		*ft_memstr_cpy(char **dst, const char *src)
{
	size_t	len_src;

	if (!src)
		return (NULL);
	len_src = ft_strlen(src);
	*dst = (char*)ft_memalloc(len_src + 1);
	*dst = ft_strcpy(*dst, src);
	return (*dst);
}
