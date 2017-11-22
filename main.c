/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:05:01 by dmelehov          #+#    #+#             */
/*   Updated: 2017/06/10 17:47:57 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_manager(int error_num)
{
	if (error_num == 1)
		write(1, "error: wrong number of arguments\n", 28);
	else if (error_num == 2)
		write(1, "error: invalid file\n", 20);
	exit(-1);
}

int		my_keys(int key, t_fdf *fdf)
{
	if (key == 53)
		exit(1);
	if (key == 126)
		fdf->rot_x += 0.0872665;
	if (key == 125)
		fdf->rot_x -= 0.0872665;
	if (key == 124)
		fdf->rot_z += 0.0872665;
	if (key == 123)
		fdf->rot_z -= 0.0872665;
	start_fucking(fdf);
	return (0);
}

void	create_struct(t_fdf *fdf)
{
	update_buff(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, X, Y, "fdf");
	fdf->img = mlx_new_image(fdf->mlx, X, Y);
	fdf->rot_x = -0.615472907;
	fdf->rot_z = 0.785398;
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		error_manager(1);
	if (parse_map(argv[1], &fdf))
		error_manager(2);
	center_map(&fdf);
	create_struct(&fdf);
	start_fucking(&fdf);
	return (0);
}
