/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 01:35:59 by dmelehov          #+#    #+#             */
/*   Updated: 2017/06/10 19:15:49 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define Y		1280
# define X		1280
# define BASE "0123456789ABCDEF"

# include "libft/includes/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

typedef	struct	s_pix
{
	double		x;
	double		y;
	double		z;
	int			col;
}				t_pix;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_pix		**home;
	t_pix		**buff;
	int			lx;
	int			ly;
	double		rot_x;
	double		rot_z;
	void		*img;
}				t_fdf;

int				my_keys(int key, t_fdf *fdf);
void			create_struct(t_fdf *fdf);
int				my_keys(int key, t_fdf *fdf);
void			error_manager(int error_num);
void			start_fucking(t_fdf *fdf);
void			draw_line(t_pix *lalka, t_pix *suka, t_fdf *fdf);
void			ft_move_angle(t_pix *home, t_pix *buff, t_fdf *fdf);
void			draw_map(t_fdf *fdf);
void			center_map(t_fdf *fdf);
void			update_buff(t_fdf *fdf);
int				parse_map(char *map, t_fdf *fdf);
int				ft_getpixdata(char *map, t_fdf *fdf);
int				ft_check_col(char *s);
int				ft_get_col(char *str);

#endif
