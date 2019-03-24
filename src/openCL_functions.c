/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:05:02 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 18:56:17 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int		read_kernel(char **arr)
{
	int	fd;
	int	rd;

	if ((fd = open("./src/fractal.cl", O_RDONLY)) < 0)
	{
		perror("Failed to load kernel");
		exit(1);
	}
	if (!(*arr = ft_memalloc(sizeof(char) * MAX_SOURCE_SIZE)))
		return (ft_error(2));
	if ((rd = read(fd, *arr, MAX_SOURCE_SIZE)) < 0)
	{
		perror("Failed to load kernel");
		exit(1);
	}
	close(fd);
	return (rd);
}

void	initialize_program(t_opencl_conf *cl)
{
	cl->source_size = read_kernel(&cl->source_str);
	cl->ret = clGetPlatformIDs(1, &cl->platform, &cl->ret_num_platforms);
	cl->ret = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 1,
		&cl->device, &cl->ret_num_devices);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &cl->ret);
	cl->q = clCreateCommandQueue(cl->context, cl->device, 0, &cl->ret);
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)
		&cl->source_str, (const size_t *)&cl->source_size, &cl->ret);
	cl->ret = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->program, "fractal", &cl->ret);
	cl->g_size[0] = W;
	cl->g_size[1] = H;
	cl->l_size[0] = 8;
	cl->l_size[1] = 8;
}

int		render(void *param)
{
	t_conf	*conf;

	conf = (t_conf*)param;
	conf->cl->setup = clCreateBuffer(conf->cl->context,
	CL_MEM_READ_ONLY, sizeof(t_setup), NULL, &conf->cl->ret);
	conf->cl->image = clCreateBuffer(conf->cl->context,
	CL_MEM_READ_ONLY, W * H * sizeof(int), NULL, &conf->cl->ret);
	conf->cl->ret = clEnqueueWriteBuffer(conf->cl->q, conf->cl->image,
	CL_TRUE, 0, W * H * sizeof(int), conf->data, 0, NULL, NULL);
	conf->cl->ret = clEnqueueWriteBuffer(conf->cl->q, conf->cl->setup, CL_TRUE,
	0, sizeof(t_setup), conf->setup, 0, NULL, NULL);
	conf->cl->ret = clSetKernelArg(conf->cl->kernel, 0, sizeof(cl_mem),
	(void *)&conf->cl->image);
	conf->cl->ret = clSetKernelArg(conf->cl->kernel, 1, sizeof(cl_mem),
	(void *)&conf->cl->setup);
	conf->cl->ret = clEnqueueNDRangeKernel(conf->cl->q, conf->cl->kernel, 2,
	NULL, conf->cl->g_size, conf->cl->l_size, 0, NULL, NULL);
	conf->cl->ret = clEnqueueReadBuffer(conf->cl->q, conf->cl->image, CL_TRUE,
	0, W * H * sizeof(int), conf->data, 0, NULL, NULL);
	conf->cl->ret = clReleaseMemObject(conf->cl->image);
	conf->cl->ret = clReleaseMemObject(conf->cl->setup);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
	return (0);
}
