/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:04:13 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/18 17:35:02 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../includes/fractol.h"
#include "../minilibx/mlx.h"
#include <math.h>

void	julia_set(t_conf *conf, t_fractal *fract)
{
	int	x;
	int	y;
	int		i;
	t_rgb	color;

  //pick some values for the constant c, this determines the shape of the Julia Set

//loop through every pixel
	y = -1;
	while(++y < H)
	{
		x = -1;
		while (++x < W)
		{
			fract->new_r = 1.5 * (x - W / 2) / (0.5 * fract->zoom * W) + fract->moveX;
			fract->new_i = (y - H / 2) / (0.5 * fract->zoom * H) + fract->moveY;
			i = -1;
			while (++i < fract->iters)
			{
				fract->old_r = fract->new_r;
				fract->old_i = fract->new_i;
				fract->new_r = fract->old_r * fract->old_r - fract->old_i * fract->old_i + fract->c_r;
				fract->new_i = 2 * fract->old_r * fract->old_i + fract->c_i;
				if ((fract->new_r * fract->new_r + fract->new_i * fract->new_i) > 4)
					break;
			}
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
		//	hsv.H = i % 256;
		//	hsv.S = 255;
		//	hsv.V = 255 * (i < iters);
//			HSV2RGB(&color, i % 360, 255, 255 * (i < iters));
			//draw the pixel
//			printf("%d\n", x * y);
//			printf("r: %d\tg: %d\tb: %d\n", color.R, color.G, color.B);
//			conf->data[x + (y * conf->pitch)] = (color.R << 16) + (color.G << 8) + color.B;
// добавить градиент
			if (i != fract->iters)
				conf->data[x + (y * conf->pitch)] = HSVToRGB(&color, i % 360, 0.5, 1. * (i < fract->iters));
			else
				conf->data[x + (y * conf->pitch)] = 0xffffff;
		}
	}
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
} */