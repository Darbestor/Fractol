/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:47:32 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 19:00:16 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../minilibx/mlx.h"
#include "../Libft/libft.h"
#include <stdlib.h>

t_conf	*mlx_new(void)
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
	if (!(mlx->cl = ft_memalloc(sizeof(t_opencl_conf) * 1)))
		return (NULL);
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
	else if (err == 2)
		write(2, "Memory allocation failure\n", 26);
	exit(0);
	return (0);
}

int		init_setup(char *argv, t_setup **src)
{
	t_setup *setup;

	if (!(setup = ft_memalloc(sizeof(t_setup) * 1)))
		return (ft_error(2));
	setup->iters = 300;
	setup->zoom = 1;
	setup->move_x = 0;
	setup->move_y = 0;
	setup->c_r = 0;
	setup->c_i = 0;
	if (!ft_strcmp(argv, "Mandelbrot"))
		setup->type = 1;
	else if (!ft_strcmp(argv, "Julia"))
	{
		setup->type = 2;
		setup->c_r = 0.285;
		setup->c_i = 0.00001;
	}
	else if (!ft_strcmp(argv, "Burningship"))
		setup->type = 3;
	else
		return (ft_error(3));
	*src = setup;
	return (0);
}

int		main(int argc, char **argv)
{
	t_conf		*conf;
	t_setup		*setup;

	setup = NULL;
	if (argc > 1)
	{
		if (!(conf = mlx_new()))
			return (ft_error(2));
		init_setup(argv[1], &setup);
		conf->setup = setup;
		initialize_program(conf->cl);
		render(conf);
		mlx_hook(conf->win, 2, 0, &key_press, conf);
		mlx_hook(conf->win, 17, 0, &close_window, conf);
		mlx_hook(conf->win, 4, 0, &mouse_press, conf);
		mlx_hook(conf->win, 6, 0, &mouse_move, conf);
		mlx_loop(conf->mlx);
	}
	return (ft_error(1));
}
