
typedef struct s_test
{
	double		zoom;
	double		moveX;
	double		moveY;
	double		iters;
	int			type;
}				t_test;

__kernel void	mandelbrot_set(__global int *arr, t_test params)
{
	int		x;
	int		y;
	int	scr_w;
	int	scr_h;
	double	c_r;
	double	c_i;
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

	c_r = 1.5 * (x - scr_w / 2) / (0.5 * params.zoom * scr_w) + params.moveX - 0.5;
	c_i = (y - scr_h / 2) / (0.5 * params.zoom * scr_h) + params.moveY;
	i = -1;
	new_i = (params.type == 2) ? c_i : 0;
	new_r = (params.type == 2) ? c_r : 0;
	while (++i < params.iters && ((mod = new_r * new_r + new_i * new_i)) <= 4)
	{
		old_r = new_r;
		old_i = new_i;
		new_r = old_r * old_r - old_i * old_i + c_r;
		new_i = 2 * old_r * old_i + c_i;
	}
	if (i != params.iters)
	{
		arr[x + (y * scr_w)] = (int)(sqrt(i / params.iters) * 255);
	}
	else
		arr[x + (y * scr_w)] = 0;
}