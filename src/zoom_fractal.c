/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 18:46:09 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/24 19:00:16 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	zoom_in(t_setup *setup, int x, int y)
{
	setup->iters += 2;
	setup->move_x += (((x > W / 2) ? ((double)x / W - 0.5) :
		-(0.5 - (double)x / (double)W)) / setup->zoom);
	setup->move_y += (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
		-0.67 * (0.5 - (double)y / (double)H)) / setup->zoom);
	setup->zoom *= 1.5;
}

void	zoom_out(t_setup *setup, int x, int y)
{
	if (setup->zoom / 1.5 >= 1)
	{
		setup->iters -= 2;
		setup->move_x -= (((x > W / 2) ? ((double)x / W - 0.5) :
		-(0.5 - (double)x / (double)W)) / setup->zoom);
		setup->move_y -= (((y > H / 2) ? 0.67 * ((double)y / H - 0.5) :
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
			zoom_in(conf->setup, x, y);
		else if (button == 5)
			zoom_out(conf->setup, x, y);
	}
	render(conf);
	return (0);
}
