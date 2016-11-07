/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:26:23 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/02 11:21:42 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_ishexa(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '0')
	{
		++i;
		if (str[i] == 'x')
		{
			++i;
			while (i <= 7)
			{
				if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0')
					return (i);
				else if ((str[i] >= '0' && str[i] <= '9') ||
					(str[i] >= 'A' && str[i] <= 'F') ||
					(str[i] >= 'a' && str[i] <= 'f'))
					++i;
				else
					return (0);
			}
			return (i);
		}
	}
	return (0);
}

static void	compute_tall(char *str, t_mlx *fdf)
{
	static int	last = 0;
	int			i;

	i = 0;
	while (ft_isdigit(str[i]))
		++i;
	if (last < i)
	{
		if (i >= 4)
			fdf->tall = 2;
		else if (i == 3)
			fdf->tall = 4;
		else
			fdf->tall = 8;
		last = i;
	}
}

static int	is_valid_digit(char *line, t_error *err, t_mlx *fdf)
{
	if (ft_isspace(line[err->i]) == 1)
	{
		if (err->i != 0)
			++(err->elem);
		while (ft_isspace(line[err->i]) == 1)
			++(err->i);
	}
	else if (ft_isdigit(line[err->i]))
	{
		compute_tall(&line[err->i], fdf);
		++(err->i);
		if (line[err->i] == ',')
		{
			++(err->i);
			if ((err->size = ft_ishexa(&line[err->i])) != 0)
				err->i += err->size;
			else
				return (-1);
		}
	}
	else
		return (-1);
	return (1);
}

static int	error_line(char *line, t_mlx *fdf)
{
	t_error		err;

	err.i = 0;
	err.digit = NULL;
	err.elem = 1;
	while (line[err.i])
	{
		if (line[err.i] == '-')
			++(err.i);
		if (is_valid_digit(line, &err, fdf) != 1)
			return (-1);
	}
	if (ft_isspace(line[err.i - 1]) == 1)
		--(err.elem);
	return (err.elem);
}

void		error_map(t_mlx *fdf, char *filename)
{
	int		check;
	int		fd;
	char	*line;
	int		i;

	fdf->map.file = ft_memstr_cpy(&(fdf->map.file), filename);
	fd = open(fdf->map.file, O_RDONLY);
	if (fd <= 0)
		mlx_exit(-1, fdf, "error_map, can't open file");
	if (get_next_line(fd, &line) <= 0)
		mlx_exit(-1, fdf, "error_map, empty file or opening folder");
	if ((fdf->map.length = error_line(line, fdf)) == -1)
		mlx_exit(-1, fdf, "error_map, wrong map format");
	fdf->map.height = 1;
	free(line);
	i = 0;
	while (get_next_line(fd, &line))
	{
		ft_printf("CHECKING LINE %d\r", i++);
		if ((check = error_line(line, fdf)) != fdf->map.length || check == -1)
			mlx_exit(-1, fdf, "error_map, wrong map format");
		++(fdf->map.height);
		free(line);
	}
	close(fd);
}
