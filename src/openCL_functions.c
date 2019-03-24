/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:05:02 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/21 22:41:41 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fractol.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Libft/libft.h"


const char * get_error_string(cl_int err)
{
         switch(err){
             case 0: return "CL_SUCCESS";
             case -1: return "CL_DEVICE_NOT_FOUND";
             case -2: return "CL_DEVICE_NOT_AVAILABLE";
             case -3: return "CL_COMPILER_NOT_AVAILABLE";
             case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
             case -5: return "CL_OUT_OF_RESOURCES";
             case -6: return "CL_OUT_OF_HOST_MEMORY";
             case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
             case -8: return "CL_MEM_COPY_OVERLAP";
             case -9: return "CL_IMAGE_FORMAT_MISMATCH";
             case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
             case -11: return "CL_BUILD_PROGRAM_FAILURE";
             case -12: return "CL_MAP_FAILURE";

             case -30: return "CL_INVALID_VALUE";
             case -31: return "CL_INVALID_DEVICE_TYPE";
             case -32: return "CL_INVALID_PLATFORM";
             case -33: return "CL_INVALID_DEVICE";
             case -34: return "CL_INVALID_CONTEXT";
             case -35: return "CL_INVALID_QUEUE_PROPERTIES";
             case -36: return "CL_INVALID_COMMAND_QUEUE";
             case -37: return "CL_INVALID_HOST_PTR";
             case -38: return "CL_INVALID_MEM_OBJECT";
             case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
             case -40: return "CL_INVALID_IMAGE_SIZE";
             case -41: return "CL_INVALID_SAMPLER";
             case -42: return "CL_INVALID_BINARY";
             case -43: return "CL_INVALID_BUILD_OPTIONS";
             case -44: return "CL_INVALID_PROGRAM";
             case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
             case -46: return "CL_INVALID_KERNEL_NAME";
             case -47: return "CL_INVALID_KERNEL_DEFINITION";
             case -48: return "CL_INVALID_KERNEL";
             case -49: return "CL_INVALID_ARG_INDEX";
             case -50: return "CL_INVALID_ARG_VALUE";
             case -51: return "CL_INVALID_ARG_SIZE";
             case -52: return "CL_INVALID_KERNEL_ARGS";
             case -53: return "CL_INVALID_WORK_DIMENSION";
             case -54: return "CL_INVALID_WORK_GROUP_SIZE";
             case -55: return "CL_INVALID_WORK_ITEM_SIZE";
             case -56: return "CL_INVALID_GLOBAL_OFFSET";
             case -57: return "CL_INVALID_EVENT_WAIT_LIST";
             case -58: return "CL_INVALID_EVENT";
             case -59: return "CL_INVALID_OPERATION";
             case -60: return "CL_INVALID_GL_OBJECT";
             case -61: return "CL_INVALID_BUFFER_SIZE";
             case -62: return "CL_INVALID_MIP_LEVEL";
             case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
             default: return "Unknown cl error";
         }
}

void	devices() {

    unsigned int i, j;
    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
	cl_uint		work_item;
 
    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    for (i = 0; i < platformCount; i++) {

        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // for each device print critical attributes
        for (j = 0; j < deviceCount; j++) {

            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            printf("%d. Device: %s\n", j+1, value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d Hardware version: %s\n", j+1, 1, value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf(" %d.%d Software version: %s\n", j+1, 2, value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d cl C version: %s\n", j+1, 3, value);
            free(value);

            // print support extensions
			clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
                    sizeof(cl_uint), &work_item, &valueSize);
            printf(" %d.%d Max Work item: %d\n", j+1, 4, work_item);

        }

        free(devices);

    }

    free(platforms);

}

int	read_kernel(char **arr)
{
	int	fd;
	int	rd;

	if ((fd = open("./src/mandelbrot.cl", O_RDONLY)) < 0)
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
	cl->ret = clGetDeviceIDs( cl->platform, CL_DEVICE_TYPE_GPU, 1, 
		&cl->device, &cl->ret_num_devices);
	cl->context = clCreateContext( NULL, 1, &cl->device, NULL, NULL, &cl->ret);
	cl->q = clCreateCommandQueue(cl->context, cl->device, 0, &cl->ret);
	cl->program = clCreateProgramWithSource(cl->context, 1,  (const char **)
		&cl->source_str, (const size_t *)&cl->source_size, &cl->ret);
	if ((cl->ret = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL)))
		printf("%s\n", get_error_string(cl->ret));
	cl->kernel = clCreateKernel(cl->program, "mandelbrot_set", &cl->ret);
	cl->g_size[0] = W;
	cl->g_size[1] = H;
	cl->l_size[0] = 8;
	cl->l_size[1] = 8;
}

int	render(void *param)
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