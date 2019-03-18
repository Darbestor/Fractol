/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:41:42 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/18 18:56:03 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W 1500
# define H 1000
# define THREADS 24
# define ABS(X) ((X) < 0 ? -(X) : (X))
# include <stdio.h>
# include <pthread.h>

typedef struct		s_rgb
{
	int				rgb;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
	int				f;
	int				p;
	int				q;
	int				t;
}					t_rgb;

typedef struct s_conf
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bits;
	int			pitch;
	int			endian;
	int			type;
	int			perm_change;
	int			mouse_prev_x;
	int			mouse_prev_y;
	double		zoom;
	double		moveX;
	double		moveY;
	double		iters;
}				t_conf;

typedef struct s_thread
{
	int			x;
	int			y;
	int			scr_w;
	int			scr_h;
	double		c_r;
	double		c_i;
	double		new_r;
	double		new_i;
	double		old_r;
	double		old_i;

	pthread_t	thread;
	t_conf		*conf;
// testing colors
	double	max;
	double	min;
	double	distance;
	/////////////
}				t_thread;

typedef struct	s_point{
	double		x;
	double		y;
}				t_point;

int		key_press(int keycode, void *param);
int		close_window(t_conf *param);
//void	julia_set(t_conf *conf, t_fractal *fract);
void	mandelbrot_set(t_conf * conf, t_thread *thread);
//void	burning_ship_set(t_conf *conf, t_fractal *fract);
//void	launch_fract(t_conf *conf, t_fractal *fract);
int		mouse_press(int button, int x, int y, void *param);
int		HSVToRGB(t_rgb *rgb, double h, double s, double v);
//int		mouse_move(int x, int y, void *param);
int		paralle_fractal(t_conf* conf);


#endif