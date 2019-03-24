/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:20:22 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 18:25:25 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

int close_window(t_conf *conf)
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
		conf->setup->moveX -= 0.1 / conf->setup->zoom;
	else if (keycode == 124)
		conf->setup->moveX += 0.1 / conf->setup->zoom;
	else if (keycode == 125)
		conf->setup->moveY -= 0.1 / conf->setup->zoom;
	else
		conf->setup->moveY += 0.1 / conf->setup->zoom;
	render(conf);
}

void	zoom_in(t_setup *setup, int x, int y)
{
	setup->iters += 2;
	setup->moveX += (((x > W / 2) ? ((double)x / W - 0.5) :
		-(0.5 - (double)x / (double)W)) / setup->zoom);
	setup->moveY += (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
		-0.67 * (0.5 - (double)y / (double)H)) / setup->zoom);
	setup->zoom *= 1.5;
}

void	zoom_out(t_setup *setup, int x, int y)
{
	if (setup->zoom / 1.5 >= 1)
	{
		setup->iters -= 2;
		setup->moveX -= (((x > W / 2) ? ((double)x / W - 0.5) :
		-(0.5 - (double)x / (double)W)) / setup->zoom);
		setup->moveY -= (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
		-0.67 * (0.5 - (double)y / (double)H)) / setup->zoom);
		setup->zoom /= 1.5;
	}
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_conf	*conf;

	conf = (t_conf*)param;
	if (x < W && x >= 0 && y < H && y >= 0)
	{
		if (button == 4)
			zoom_in(conf->setup, x ,y);
		else if (button == 5)
			zoom_out(conf->setup, x ,y);
	}
	render(conf);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_conf *conf;

	conf = (t_conf*)param;
	if (conf->perm_change && x >= 0 && x < W && y >= 0 && y < H)
	{
		conf->setup->c_i = ((double)y / H);
		conf->setup->c_r = ((double)x / W * 2) - 1.5;
		printf("c_i %f\tc_r %f\n", conf->setup->c_i, conf->setup->c_r);
		printf("x %d\ty %d\n", x, y);
/* 		if (x > conf->mouse_prev_x)
			conf->setup->c_r += 0.005;
		else if (x < conf->mouse_prev_x)
			conf->setup->c_r -= 0.005;
		if (y > conf->mouse_prev_y)
			conf->setup->c_i += 0.005;
		else if (y < conf->mouse_prev_y)
			conf->setup->c_i -= 0.005;
		conf->mouse_prev_x = x;
		conf->mouse_prev_y = y; */
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
		if (!conf->perm_change)
		{
			conf->mouse_prev_y = 0;
			conf->mouse_prev_x = 0;
		}
	}
	return (0);
}