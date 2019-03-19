/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:47:32 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/19 20:09:54 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/fractol.h"
#include "../Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
t_conf	*mlx_new()
{
	t_conf *mlx;

	if (!(mlx = ft_memalloc(sizeof(t_conf) * 1)))
		return (NULL);
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->win = mlx_new_window(mlx->mlx, W, H, "Fractol")))
		return (NULL);
	if (!(mlx->img = mlx_new_image(mlx->mlx, W, H)))
		return (NULL);
	mlx->data = (int*)mlx_get_data_addr(mlx->img, &mlx->bits, &mlx->pitch,
		&mlx->endian);
	mlx->pitch = mlx->pitch / (mlx->bits / 8);
	mlx->perm_change = 0;
	return (mlx);
}

int		ft_error(int err)
{
	if (err == 1)
	{
		write(2, "usage: ./fractol [fractals]\n", 28);
		write(2, "fractals:\n", 10);
		write(2, "\tMandelbrot\n", 12);
		write(2, "\tJulia\n", 7);
		write(2, "\tBurningship\n", 13);
	}
	else if (err == 3)
	{
		write(2, "Invalide name of fractal\n", 25);
	}
	else if (err == 4)
		write(2, "Multithreading failure\n", 23);
	else
		write(2, "Memory allocation failure\n", 26);
	exit(0);
	return(0);
}

void	*launch_fract(void *param)
{
	t_thread	*thread;

	thread = (t_thread*)param;
		if (thread->conf->type == 1)
			mandelbrot_set(thread->conf, thread);
/* 		else if (thread->conf->type == 2)
			julia_set(conf, conf->fract);
		else if (thread->conf->type == 3)
			burning_ship_set(conf, conf->fract); */
	pthread_exit(0);
}

int	set_type(int argc, char **argv, t_conf *conf)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "Mandelbrot"))
			conf->type = 1;
		else if (!ft_strcmp(argv[i], "Julia"))
			conf->type = 2;
		else if (!ft_strcmp(argv[i], "Burningship"))
			conf->type = 3;
		else
			return (0);
		i++;
	}
		return (1);
}

int	paralle_fractal(t_conf* conf)
{
	t_thread	thread[THREADS];
	int			i;

	i = -1;
	/* if (!(fract = ft_memalloc(sizeof(t_thread) * THREADS)))
		return (0); */
	while (++i < THREADS)
	{
		thread[i].conf = conf;
		thread[i].x = (W / THREADS) * i;
		thread[i].y = 0;
		thread[i].scr_w = i == THREADS - 1 ? (W / THREADS) * (i + 1) +
		W % THREADS : (W / THREADS) * (i + 1);
		if (pthread_create(&thread[i].thread, NULL, launch_fract, &(thread[i])))
			return (ft_error(4));
	}
	i = -1;
	while (++i < THREADS)
		if (pthread_join(thread[i].thread, NULL))
			return (ft_error(4));
//	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
	return (1);
}

#define MAX_SOURCE_SIZE (0x1000000)

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
             default: return "Unknown OpenCL error";
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
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf(" %d.%d OpenCL C version: %s\n", j+1, 3, value);
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





void	test_OpenCL(t_conf *conf)
{
	t_test	test;
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
 
	test.iters = conf->iters;
	test.moveX = conf->moveX;
	test.moveY = conf->moveY;
	test.zoom = conf->zoom;
	test.type = conf->type;
    fp = fopen("src/mandelbrot.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, 
            &device_id, &ret_num_devices);
 
    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 
    // Create memory buffers on the device for each vector 
    cl_mem image = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            W * H * sizeof(int), NULL, &ret);
 
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, image, CL_TRUE, 0,
            W * H * sizeof(int), conf->data, 0, NULL, NULL);

    // Create a program from the kernel source
	cl_program program;
    if (!(program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret)))
		printf("%s\n", get_error_string(ret));

 
    // Build the program
    if ((ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL)))
		printf("Error %s\n", get_error_string(ret));
 
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "mandelbrot_set", &ret);
 
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&image);
    ret = clSetKernelArg(kernel, 1, sizeof(t_test), (void *)&test);
 
    // Execute the OpenCL kernel on the list
    size_t global_item_size[2] = {W, H}; // Process the entire lists
    size_t local_item_size[2] = {8, 8}; // Divide work items into groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, 
            global_item_size, local_item_size, 0, NULL, NULL);
 
    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, image, CL_TRUE, 0, 
            W * H * sizeof(int), conf->data, 0, NULL, NULL);
    // Display the result to the screen
/*     for(i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]); */
 
    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(image);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_conf		*conf;

	if (argc > 1)
	{
		if (!(conf = mlx_new()))
			return (ft_error(2));
	//	conf->fract = fract;
		conf->zoom = 1;
		conf->moveX = 0;
		conf->moveY = 0;
		conf->iters = 100;
//		conf->c_r = -0.7;
//		conf->c_i = 0.3015;
		
		if (!set_type(argc, argv, conf))
			return (ft_error(3));
		devices();
		test_OpenCL(conf);
		mlx_hook(conf->win, 2, 0, &key_press, conf);
		mlx_hook(conf->win, 17, 0, &close_window, conf);
		mlx_hook(conf->win, 4, 0, &mouse_press, conf);
//		mlx_hook(conf->win, 6, 0, &mouse_move, conf);
		mlx_loop(conf->mlx);
	}
	return (ft_error(1));
}