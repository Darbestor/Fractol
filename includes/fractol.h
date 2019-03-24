/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:41:42 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 19:01:36 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W 2048
# define H 1024
# define ABS(X) ((X) < 0 ? -(X) : (X))
# define MAX_SOURCE_SIZE 10000
# include <unistd.h>
# include <OpenCL/cl.h>

typedef struct			s_setup
{
	double				zoom;
	double				move_x;
	double				move_y;
	double				iters;
	int					type;
	double				c_r;
	double				c_i;
}						t_setup;

typedef struct			s_opencl_conf
{
	char				*source_str;
	size_t				source_size;
	cl_platform_id		platform;
	cl_device_id		device;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	q;
	cl_mem				image;
	cl_mem				setup;
	cl_program			program;
	cl_kernel			kernel;
	size_t				g_size[2];
	size_t				l_size[2];
}						t_opencl_conf;

typedef struct			s_conf
{
	void				*mlx;
	void				*win;
	void				*img;
	int					*data;
	int					bits;
	int					pitch;
	int					endian;
	int					type;
	int					perm_change;
	t_setup				*setup;
	t_opencl_conf		*cl;
}						t_conf;

int						key_press(int keycode, void *param);
int						close_window(t_conf *param);
int						mouse_press(int button, int x, int y, void *param);
int						mouse_move(int x, int y, void *param);
int						paralle_fractal(t_conf *conf);
int						render(void *param);
int						ft_error(int err);
void					initialize_program(t_opencl_conf *cl);

#endif
