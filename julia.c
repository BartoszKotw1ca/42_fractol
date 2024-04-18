/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:45:21 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/18 13:46:52 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculation_julia(t_fract *mlx, t_point pixel, int x, int y)
{
	t_point	z;
	t_point	z_squared;

	z.i = (pixel.i + x - WIDTH) * (4.0 / WIDTH) * mlx->zoom;
	z.z = (pixel.z + y - HEIGHT) * (4.0 / HEIGHT) * mlx->zoom;;
	z_squared.i = z.i * z.i;
	z_squared.z = z.z * z.z;
	mlx->i = 0;
	while (mlx->i < mlx->max_iter && ((z_squared.i + z_squared.z) <= 4.0))
	{
		z.z = 2.0 * z.i * z.z + mlx->c.z;
		z.i = z_squared.i - z_squared.z + mlx->c.i;
		z_squared.i = z.i * z.i;
		z_squared.z = z.z * z.z;
		mlx->i++;
	}
}

void	draw_julia(t_fract *mlx, int x, int y)
{
	t_point	pixel;

	mlx->i = -1;
	mlx->max_iter = 1000;
	pixel.z = -1;
	while (mlx->i++ < 256)
		mlx->colors[mlx->i] = (mlx->i << 8);
	while (pixel.z++ < HEIGHT)
	{
		pixel.i = -1;
		while (pixel.i++ < WIDTH)
		{
			calculation_julia(mlx, pixel, x, y);
			if (mlx->i == mlx->max_iter)
				my_mlx_pixel_put(mlx, pixel.i, pixel.z, 0x000000);
			else
				my_mlx_pixel_put(mlx, pixel.i, pixel.z,
					mlx->colors[mlx->i % 256]);
		}
	}
}

void	put_julia(t_fract *mlx, int x, int y, double zoom)
{
	mlx->zoom /= zoom;
	mlx->img = mlx_new_image(mlx->con, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	draw_julia(mlx, x, y);
	mlx_put_image_to_window(mlx->con, mlx->win,
		mlx->img, 0, 0);
}

int	mouse_hook_julia(int keycode, int x, int y, t_fract *mlx)
{
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (keycode == 4)
		put_julia(mlx, mlx->mouse_x, mlx->mouse_y, 1.5);
	else if (keycode == 5)
		put_julia(mlx, mlx->mouse_x, mlx->mouse_y, 0.5);
	// else if (keycode == 1)
	// {
	// 	if (x > WIDTH - 32 && x < WIDTH - 5
	// 		&& y < -33 && y > -6)
	// 		close_window(mlx);
	// }
	printf("%d %d %d\n", keycode, x, y);
	return (0);
}

int	key_hook_julia(int keycode, t_fract *mlx)
{
	mlx_mouse_get_pos(mlx->con, mlx->win, &(mlx->mouse_x), &(mlx->mouse_y));
	if (keycode == 65307)
		close_window(mlx);
	if (keycode == 49)
		put_julia(mlx, mlx->mouse_x, mlx->mouse_y, 1.5);
	else if (keycode == 100)
		put_julia(mlx, mlx->center_x -= 10, mlx->center_y, 1);
	else if (keycode == 97)
		put_julia(mlx, mlx->center_x += 10, mlx->center_y, 1);
	else if (keycode == 115)
		put_julia(mlx, mlx->center_x, mlx->center_y -= 10, 1);
	else if (keycode == 119)
		put_julia(mlx, mlx->center_x, mlx->center_y += 10, 1);
	return (0);
}

int	closee(int keycode, t_fract *vars)
{
	exit(1);
	mlx_destroy_window(vars->con, vars->win);
	return (0);
}

void	julia_program(double x, double y)
{
	t_fract	mlx;

	mlx.con = mlx_init();
	mlx.zoom = 1.0;
	mlx.center_x = WIDTH / 2;
	mlx.center_y = HEIGHT / 2;
	mlx.c.i = x;
	mlx.c.z = y;
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractal");
	mlx.img = mlx_new_image(mlx.con, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	put_julia(&mlx, WIDTH / 2, HEIGHT / 2, 1);
	mlx_hook(mlx.win, 17, 1L<<2, closee, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook_julia, &mlx);
	mlx_key_hook(mlx.win, key_hook_julia, &mlx);
	mlx_loop(mlx.con);
}
