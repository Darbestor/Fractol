/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:22:58 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/18 17:35:08 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../includes/fractol.h"
#include "../minilibx/mlx.h"

void	burning_ship_set(t_conf *conf, t_fractal *fract)
{
	int	x;
	int	y;
	int	i;
	struct s_rgb color; //the RGB color value for the pixel

	y = -1;
	while(++y < H)
	{
		x = -1;
		while (++x < W)
		{
			fract->c_r = 1.5 * (x - W / 2) / (0.5 * fract->zoom * W) + fract->moveX - 0.5;
			fract->c_i = (y - H / 2) / (0.5 * fract->zoom * H) + fract->moveY - 0.5;
			i = -1;
			fract->new_i = 0;
			fract->new_r = 0;
			while (++i < fract->iters)
			{
				fract->old_r = fract->new_r;
				fract->old_i = fract->new_i;
				fract->new_r = fract->old_r * fract->old_r - fract->old_i * fract->old_i + fract->c_r;
				fract->new_i = 2 * ABS(fract->old_r * fract->old_i) + fract->c_i;
				if ((fract->new_r * fract->new_r + fract->new_i * fract->new_i) > 10)
					break;
			}
			if (i != fract->iters)
				conf->data[x + (y * conf->pitch)] = HSVToRGB(&color, i % 360, 1., 1. * (i < fract->iters));
			else
				conf->data[x + (y * conf->pitch)] = 0x000000;
		}
	}
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
} */