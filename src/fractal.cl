typedef struct s_setup
{
	double		zoom;
	double		move_x;
	double		move_y;
	double		iters;
	int			type;
	double		c_r;
	double	 	c_i;
}				t_setup;

__kernel void	fractal(__global int *arr, __global t_setup *params)
{
	int		x;
	int		y;
	int	scr_w;
	int	scr_h;
	double	par_r;
	double	par_i;
	int	i;
	double mod;
	double new_i;
	double new_r;
	double old_r;
	double old_i;

	x = get_global_id(0);
	y = get_global_id(1);
	scr_w = get_global_size(0);
	scr_h = get_global_size(1);
	par_r = 1.5 * (x - scr_w / 2) / (0.5 * params->zoom * scr_w) +
	params->move_x - (params->type == 2 ? 0 : 0.5);
	par_i = (y - scr_h / 2) / (0.5 * params->zoom * scr_h)
	+ params->move_y - (params->type == 3 ? 0.5 : 0);
	i = -1;
	new_i = par_i;
	new_r = par_r;
	par_r = params->c_r ? params->c_r : par_r;
	par_i = params->c_i ? params->c_i : par_i;
	while (++i < params->iters && ((mod = new_r * new_r + new_i * new_i)) <= 4)
	{
		old_r = new_r;
		old_i = new_i;
		new_r = old_r * old_r - old_i * old_i + par_r;
		new_i = 2 * (params->type == 3 ? fabs(old_r * old_i) : old_r * old_i)
		+ par_i;
	}
	if (i < params->iters)
	{
		double t = fabs((i - log(log2(mod)) / log(2.0)) / params->iters);
		int	r = (int)(9 * (1 - t) * t * t * t * 255);
		int	g = (int)( 15 * (1 - t ) * (1 - t) * t * t * 255);
		int	b =  (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		arr[x + (y * scr_w)] = (r << 16) | (g << 8) | b;
	}
	else
		arr[x + (y * scr_w)] = 0xffa31a;
}
