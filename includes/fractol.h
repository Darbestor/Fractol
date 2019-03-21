/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:41:42 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/21 21:25:12 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W 2048
# define H 1024
# define ABS(X) ((X) < 0 ? -(X) : (X))
#define MAX_SOURCE_SIZE 10000
# include <stdio.h>
# include <pthread.h>
# include <OpenCL/cl.h>

//OpenCL errors
#define CL_SUCCESS 0
    #define CL_DEVICE_NOT_FOUND -1
    #define CL_DEVICE_NOT_AVAILABLE -2
    #define CL_COMPILER_NOT_AVAILABLE -3
    #define CL_MEM_OBJECT_ALLOCATION_FAILURE -4
    #define CL_OUT_OF_RESOURCES -5
    #define CL_OUT_OF_HOST_MEMORY -6
    #define CL_PROFILING_INFO_NOT_AVAILABLE -7
    #define CL_MEM_COPY_OVERLAP -8
    #define CL_IMAGE_FORMAT_MISMATCH -9
    #define CL_IMAGE_FORMAT_NOT_SUPPORTED -10
    #define CL_BUILD_PROGRAM_FAILURE -11
    #define CL_MAP_FAILURE -12

    #define CL_INVALID_VALUE -30
    #define CL_INVALID_DEVICE_TYPE -31
    #define CL_INVALID_PLATFORM -32
    #define CL_INVALID_DEVICE -33
    #define CL_INVALID_CONTEXT -34
    #define CL_INVALID_QUEUE_PROPERTIES -35
    #define CL_INVALID_COMMAND_QUEUE -36
    #define CL_INVALID_HOST_PTR -37
    #define CL_INVALID_MEM_OBJECT -38
    #define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR -39
    #define CL_INVALID_IMAGE_SIZE -40
    #define CL_INVALID_SAMPLER -41
    #define CL_INVALID_BINARY -42
    #define CL_INVALID_BUILD_OPTIONS -43
    #define CL_INVALID_PROGRAM -44
    #define CL_INVALID_PROGRAM_EXECUTABLE -45
    #define CL_INVALID_KERNEL_NAME -46
    #define CL_INVALID_KERNEL_DEFINITION -47
    #define CL_INVALID_KERNEL -48
    #define CL_INVALID_ARG_INDEX -49
    #define CL_INVALID_ARG_VALUE -50
    #define CL_INVALID_ARG_SIZE -51
    #define CL_INVALID_KERNEL_ARGS -52
    #define CL_INVALID_WORK_DIMENSION -53
    #define CL_INVALID_WORK_GROUP_SIZE -54
    #define CL_INVALID_WORK_ITEM_SIZE -55
    #define CL_INVALID_GLOBAL_OFFSET -56
    #define CL_INVALID_EVENT_WAIT_LIST -57
    #define CL_INVALID_EVENT -58
    #define CL_INVALID_OPERATION -59
    #define CL_INVALID_GL_OBJECT -60
    #define CL_INVALID_BUFFER_SIZE -61
    #define CL_INVALID_MIP_LEVEL -62
    #define CL_INVALID_GLOBAL_WORK_SIZE -63

//

typedef struct s_setup
{
	double		zoom;
	double		moveX;
	double		moveY;
	double		iters;
	int			type;
}				t_setup;

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
	t_setup		*setup;
}				t_conf;

typedef struct	s_opencl_conf
{
	char				*source_str;
	size_t				source_size;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				image;
	cl_mem				setup;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_item_size[2];
	size_t				local_item_size[2];
}					t_opencl_conf;


int		key_press(int keycode, void *param);
int		close_window(t_conf *param);
//void	julia_set(t_conf *conf, t_fractal *fract);
//void	mandelbrot_set(t_conf * conf, t_thread *thread);
//void	burning_ship_set(t_conf *conf, t_fractal *fract);
//void	launch_fract(t_conf *conf, t_fractal *fract);
int		mouse_press(int button, int x, int y, void *param);
//int		HSVToRGB(t_rgb *rgb, double h, double s, double v);
//int		mouse_move(int x, int y, void *param);
int		paralle_fractal(t_conf* conf);
void	render(t_conf *conf);
int		ft_error(int err);


#endif