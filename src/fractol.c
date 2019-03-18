/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:47:32 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/18 19:02:19 by ghalvors         ###   ########.fr       */
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
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
	return (1);
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
		if (!paralle_fractal(conf))
		{
			printf("Error in paralleling\n");
			return (0);
		}
		//launch_fract(conf, fract);
		mlx_hook(conf->win, 2, 0, &key_press, conf);
		mlx_hook(conf->win, 17, 0, &close_window, conf);
		mlx_hook(conf->win, 4, 0, &mouse_press, conf);
//		mlx_hook(conf->win, 6, 0, &mouse_move, conf);
		mlx_loop(conf->mlx);
	}
	return (ft_error(1));
}