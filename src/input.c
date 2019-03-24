/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:20:22 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 19:00:44 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

int		close_window(t_conf *conf)
{
	conf->cl->ret = clFlush(conf->cl->q);
	conf->cl->ret = clFinish(conf->cl->q);
	conf->cl->ret = clReleaseKernel(conf->cl->kernel);
	conf->cl->ret = clReleaseProgram(conf->cl->program);
	conf->cl->ret = clReleaseCommandQueue(conf->cl->q);
	conf->cl->ret = clReleaseContext(conf->cl->context);
	(void)conf;
	exit(0);
	return (0);
}

void	move_fractal(t_conf *conf, int keycode)
{
	if (keycode == 123)
		conf->setup->move_x -= 0.1 / conf->setup->zoom;
	else if (keycode == 124)
		conf->setup->move_x += 0.1 / conf->setup->zoom;
	else if (keycode == 125)
		conf->setup->move_y -= 0.1 / conf->setup->zoom;
	else
		conf->setup->move_y += 0.1 / conf->setup->zoom;
	render(conf);
}

int		mouse_move(int x, int y, void *param)
{
	t_conf *conf;

	conf = (t_conf*)param;
	if (conf->perm_change && x >= 0 && x < W && y >= 0 && y < H)
	{
		conf->setup->c_i = ((double)y / H);
		conf->setup->c_r = ((double)x / W * 2) - 1.5;
		render(conf);
	}
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_conf	*conf;

	conf = (t_conf*)param;
	if (keycode == 53)
		close_window(conf);
	if (keycode >= 123 && keycode <= 126)
		move_fractal(conf, keycode);
	if (keycode == 35)
	{
		if (conf->setup->type == 2)
			conf->perm_change = conf->perm_change ? 0 : 1;
	}
	return (0);
}
