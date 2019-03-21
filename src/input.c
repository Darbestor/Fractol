/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:20:22 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/21 22:43:01 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

int close_window(t_conf *conf)
{
	conf->cl->ret = clFlush(conf->cl->command_queue);
    conf->cl->ret = clFinish(conf->cl->command_queue);
    conf->cl->ret = clReleaseKernel(conf->cl->kernel);
    conf->cl->ret = clReleaseProgram(conf->cl->program);
    conf->cl->ret = clReleaseCommandQueue(conf->cl->command_queue);
    conf->cl->ret = clReleaseContext(conf->cl->context);
	(void)conf;
	exit(0);
	return (0);
}

void	move_fractal(t_conf *conf, int keycode)
{
	if (keycode == 123)
		conf->moveX -= 0.1;
	else if (keycode == 124)
		conf->moveX += 0.1;
	else if (keycode == 125)
		conf->moveY -= 0.1;
	else
		conf->moveY += 0.1;
//	launch_fract(conf, conf->fract);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_conf	*conf;

	conf = (t_conf*)param;
	if (x < W && x >= 0 && y < H && y >= 0)
    {
        if (button == 4)
        {
            conf->setup->moveX += (((x > W / 2) ? ((double)x / W - 0.5) :
                -(0.5 - (double)x / (double)W)) / conf->setup->zoom);
            conf->setup->moveY += (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
                -0.67 * (0.5 - (double)y / (double)H)) / conf->setup->zoom);
           conf->setup->zoom *= 1.5;
			conf->setup->iters += 2;
        }
        else if (button == 5)
        {
            conf->setup->zoom /= 1.5;
            conf->setup->moveX -= (((x > W / 2) ? ((double)x / W - 0.5) :
                -(0.5 - (double)x / (double)W)) / conf->setup->zoom);
            conf->setup->moveY -= (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
                -0.67 * (0.5 - (double)y / (double)H)) / conf->setup->zoom);
			conf->setup->iters -= 2;
        }
    }
	render(conf);
	return (0);
}

/* int		mouse_move(int x, int y, void *param)
{
	t_conf *conf;
	(void)y;
	(void)x;
	conf = (t_conf*)param;
	if (conf->perm_change)
	{
		if (x > conf->mouse_prev_x)
			conf->c_r += 0.01;
		else if (x < conf->mouse_prev_x)
			conf->c_r -= 0.01;
		if (y > conf->mouse_prev_y)
			conf->c_i += 0.01;
		else if (y < conf->mouse_prev_y)
			conf->c_i -= 0.01;
		conf->mouse_prev_x = x;
		conf->mouse_prev_y = y;
//		launch_fract(conf, conf->fract);
	}
	return (0);
} */

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
		if (conf->type == 2)
			conf->perm_change = conf->perm_change ? 0 : 1;
		if (!conf->perm_change)
		{
			conf->mouse_prev_y = 0;
			conf->mouse_prev_x = 0;
		}
	}
	return (0);
}