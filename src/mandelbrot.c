/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:22 by ghalvors          #+#    #+#             */
/*   Updated: 2019/03/21 20:35:17 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../minilibx/mlx.h"
#include "../Libft/libft.h"
#include <math.h>

/* void	choose_case(t_rgb *rgb, int cs, int v)
{
	if (cs == 0)
		rgb->rgb = (v << 16) | (rgb->t << 8) | rgb->p;
	else if (cs == 1)
		rgb->rgb = (rgb->q << 16) | (v << 8) | rgb->p;
	else if (cs == 2)
		rgb->rgb = (rgb->p << 16) | (v << 8) | rgb->t;
	else if (cs == 3)
		rgb->rgb = (rgb->p << 16) | (rgb->q << 8) | v;
	else if (cs == 4)
		rgb->rgb = (rgb->t << 16) | (rgb->p << 8) | v;
	else
		rgb->rgb = (v << 16) | (rgb->p << 8) | rgb->q;
	rgb->B = (rgb->rgb >> 16) & 0xFF;
	rgb->G = (rgb->rgb >> 8) & 0xFF;
	rgb->R = (rgb->rgb) & 0xFF;
}

int		HSVToRGB(t_rgb *rgb, double h, double s, double v)
{
	int i;

	if (s == 0)
		rgb->rgb = (((int)v * 255) << 16) | (((int)v * 255) << 8)
		| ((int)v * 255);
	else
	{
		if (h == 360)
			h = 0;
		else
			h = h / 60;
		i = (int)trunc(h);
		rgb->f = h - i;
		rgb->p = (v * (1.0 - s)) * 255;
		rgb->q = (v * (1.0 - (s * rgb->f))) * 255;
		rgb->t = (v * (1.0 - (s * (1.0 - rgb->f)))) * 255;
		choose_case(rgb, i, v * 255);
	}
	return (rgb->rgb);
}

void	mandelbrot_set(t_conf* conf, t_thread *thread)
{
	int		x;
	double	i;
	double mod;
//	t_rgb	color; //the RGB color value for the pixel

//printf("Initial vals: X: %d\tY: %d\n", thread->x, thread->y);
	while(thread->y < H)
	{
		x = thread->x - 1;
		while (++x < thread->scr_w)
		{
			thread->c_r = 1.5 * (x - W / 2) / (0.5 * conf->zoom * W) + conf->moveX - 0.5;
			thread->c_i = (thread->y - H / 2) / (0.5 * conf->zoom * H) + conf->moveY;
			if (x == 2000 && thread->y == 1000)
				printf("pthread: %f\t%f\n", thread->c_r, thread->c_i);
			i = -1;
			thread->new_i = 0;
			thread->new_r = 0;
			while (++i < conf->iters && ((mod = thread->new_r * thread->new_r + thread->new_i * thread->new_i)) <= 4)
			{
				thread->old_r = thread->new_r;
				thread->old_i = thread->new_i;
				thread->new_r = thread->old_r * thread->old_r - thread->old_i * thread->old_i + thread->c_r;
				thread->new_i = 2 * thread->old_r * thread->old_i + thread->c_i;
			}
			if (i != conf->iters)
			{
				conf->data[x + (thread->y * conf->pitch)] = (sqrt(i / conf->iters) * 255);
			}
			else
				conf->data[x + (thread->y * conf->pitch)] = 0x000000;
		}
		thread->y++;
	}
	//printf("end vals: X: %d\tY: %d\n", x, thread->y);
} */


// insert above i != iters
			/* 	f_part = modf(i / 255., &i_part); */
/* 				double z = sqrt(mod);
				int bright = 256. * log2(1.75 + i - log2(log2(z))) / log2(thread->iters);
				color.R = bright;
				color.G = bright;
				color.B = 255;
				conf->data[x + (y * conf->pitch)] = (color.R << 16) | (color.G << 8) | color.B; */
				//conf->data[x + (y * conf->pitch)] = pallete[i];
				//i =  i - log(log(mod)/log(2.0));
/* 				color.R = (int)(9*(1-t)*t*t*t*255);
 				color.G = (int)(15*(1-t)*(1-t)*t*t*255);
 				color.B =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255); */
/* 				i = (i - log(log2(sqrt(mod))) / log(2.0)) / thread->iters;
				color.R = i * 255;
 				color.G = 255 * i;
 				color.B =  255 * i;
				if (i >= 1)
					printf("%f\n", i);
				color.rgb = (color.R << 16) | (color.G << 8) | color.B;
				conf->data[x + (y * conf->pitch)] = color.rgb; */
				//conf->data[x + (y * conf->pitch)] = HSVToRGB(&color, 255 * sin(i), 1., 1.);