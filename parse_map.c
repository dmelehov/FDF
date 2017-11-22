/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:39:22 by dmelehov          #+#    #+#             */
/*   Updated: 2017/06/10 18:20:08 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_col(char *str)
{
	int	i;
	int	p;
	int	k;
	int	s;

	k = 0;
	i = 0;
	s = 1;
	while (str[k])
		k++;
	k--;
	while (k >= 0)
	{
		p = 0;
		while (BASE[p] != ft_toupper(str[k]))
			p++;
		i = i + (p * s);
		k--;
		s = s * 16;
	}
	return (i);
}

int		ft_check_col(char *s)
{
	if (s == NULL)
		return (0xFFFFFF);
	return (ft_get_col(s + 3));
}

int		ft_getpixdata(char *map, t_fdf *fdf)
{
	int		x;
	int		y;
	int		fd;
	char	*line;
	char	**arr;

	fd = open(map, O_RDONLY);
	y = 0;
	fdf->home = (t_pix **)malloc(sizeof(t_pix *) * fdf->ly);
	while (get_next_line(fd, &line) > 0)
	{
		fdf->home[y] = (t_pix *)malloc(sizeof(t_pix) * fdf->lx);
		x = -1;
		arr = ft_strsplit(line, ' ');
		while (++x < fdf->lx)
		{
			if (arr[x])
				fdf->home[y][x].z = ft_atoi(arr[x]);
			else
				return (1);
			fdf->home[y][x].col = ft_check_col(ft_strchr(arr[x], ','));
		}
		y++;
	}
	return (0);
}

int		parse_map(char *map, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**arr;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (1);
	fdf->ly = 0;
	fdf->lx = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (fdf->ly == 0)
		{
			arr = ft_strsplit(line, ' ');
			while (arr[fdf->lx])
				fdf->lx++;
		}
		fdf->ly++;
	}
	if (fdf->lx < 2 || fdf->ly < 2)
		return (1);
	return (ft_getpixdata(map, fdf));
}

void	update_buff(t_fdf *fdf)
{
	int i;

	i = -1;
	fdf->buff = (t_pix **)malloc(sizeof(t_pix *) * fdf->ly);
	while (++i < fdf->ly)
		fdf->buff[i] = (t_pix *)malloc(sizeof(t_pix ) * fdf->lx);
}
