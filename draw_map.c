/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:45:40 by dmelehov          #+#    #+#             */
/*   Updated: 2017/06/10 18:27:48 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->ly)
	{
		x = 0;
		while (x < fdf->lx)
		{
			fdf->home[y][x].x = (double)(-fdf->lx / 2 + x) * X / fdf->lx / 1.41;
			fdf->home[y][x].y = (double)(-fdf->ly / 2 + y) * X / fdf->lx / 1.41;
			fdf->home[y][x].z = (double)(fdf->home[y][x].z) * X / fdf->lx / 1.41;
			x++;
		}
		y++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->ly)
	{
		x = 0;
		while (x < fdf->lx)
		{
			mlx_pixel_put(fdf->mlx, fdf->win, fdf->home[y][x].x + X / 2,
				fdf->home[y][x].y + Y / 2, fdf->home[y][x].col);
			x++;
		}
		y++;
	}
	mlx_loop(fdf->mlx);
}

void	ft_move_angle(t_pix *home, t_pix *buff, t_fdf *fdf)
{
	buff->x = home->x * cos(fdf->rot_z) - home->y * sin(fdf->rot_z) + X / 2;
	buff->y = (home->x * sin(fdf->rot_z) + home->y * cos(fdf->rot_z))
		* cos(fdf->rot_x) + home->z * sin(fdf->rot_x) + Y / 2;
	buff->col = home->col;
}

void	draw_line(t_pix *lalka, t_pix *suka, t_fdf *fdf)
{
	int x;
	int y;

	if (abs((int)lalka->x - (int)suka->x) >= abs((int)lalka->y - (int)suka->y))
	{
		x = lalka->x;
		while (x != (int)suka->x)
		{
			y = (suka->y - lalka->y) / (suka->x - lalka->x)
				* (x - lalka->x) + lalka->y;
			mlx_pixel_put(fdf->mlx, fdf->win, x, y, suka->col);
			lalka->x > suka->x ? x-- : x++;
		}
	}
	else
	{
		y = lalka->y;
		while (y != (int)suka->y)
		{
			x = (suka->x - lalka->x) / (suka->y - lalka->y)
				* (y - lalka->y) + lalka->x;
			mlx_pixel_put(fdf->mlx, fdf->win, x, y, suka->col);
			lalka->y > suka->y ? y-- : y++;
		}
	}
}

void	start_fucking(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	while (y < fdf->ly)
	{
		x = 0;
		while (x < fdf->lx)
		{
			ft_move_angle(&fdf->home[y][x], &fdf->buff[y][x], fdf);
			mlx_pixel_put(fdf->mlx, fdf->win,
				fdf->buff[y][x].x, fdf->buff[y][x].y, fdf->home[y][x].col);
			if (x != 0)
				draw_line(&fdf->buff[y][x], &fdf->buff[y][x - 1], fdf);
			if (y != 0)
				draw_line(&fdf->buff[y][x], &fdf->buff[y - 1][x], fdf);
			x++;
		}
		y++;
	}
	mlx_hook(fdf->win, 2, 0, my_keys, fdf);
	mlx_loop(fdf->mlx);
}
