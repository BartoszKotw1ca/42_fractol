/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:45:03 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/19 14:54:33 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// In an RGB color, the value is usually a 24-bit number where:
// 	The 8 least significant bits (rightmost) represent the blue component.
// 	The next 8 bits represent the green component.
// 	The 8 most significant bits (leftmost) represent the red component.
// 	color = red | (green << 8) | (blue << 16)
// int a = 60;    /* 60 = 0011 1100 */
// int b = 13;    /* 13 = 0000 1101 */
// result = a | b; /*result = 61 = 0011 1101
void	calculation_mandel(t_fract *mlx, t_point *c)
{
	t_point	z;
	t_point	z_squared;

	z = *c;
	z_squared.i = z.i * z.i;
	z_squared.z = z.z * z.z;
	mlx->i = 0;
	while (mlx->i < mlx->max_iter && ((z_squared.i + z_squared.z) <= 4.0))
	{
		z.z = 2.0 * z.i * z.z + c->z;
		z.i = z_squared.i - z_squared.z + c->i;
		z_squared.i = z.i * z.i;
		z_squared.z = z.z * z.z;
		mlx->i ++;
	}
}

void	draw_mandelbrot(t_fract *mlx, int x, int y)
{
	t_point	pixel;
	t_point	c;

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
			c.i = (pixel.i + x - WIDTH) * (4.0 / WIDTH) * mlx->zoom;
			c.z = (pixel.z + y - HEIGHT) * (4.0 / HEIGHT) * mlx->zoom;
			calculation_mandel(mlx, &c);
			if (mlx->i == mlx->max_iter)
				my_mlx_pixel_put(mlx, pixel.i, pixel.z, 0x000000);
			else
				my_mlx_pixel_put(mlx, pixel.i, pixel.z,
					mlx->colors[mlx->i % 256]);
		}
	}
}

void	put_mandelbrot(t_fract *mlx, int x, int y, double zoom)
{
	mlx->zoom /= zoom;
	mlx->img = mlx_new_image(mlx->con, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	draw_mandelbrot(mlx, x, y);
	mlx_put_image_to_window(mlx->con, mlx->win,
		mlx->img, 0, 0);
}

int	mouse_hook_mandelbrot(int keycode, int x, int y, t_fract *mlx)
{
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (keycode == 4)
		put_mandelbrot(mlx, mlx->mouse_x, mlx->mouse_y, 1.5);
	else if (keycode == 5)
		put_mandelbrot(mlx, mlx->mouse_x, mlx->mouse_y, 0.5);
	return (0);
}

int	key_hook_mandel(int keycode, t_fract *mlx)
{
	mlx_mouse_get_pos(mlx->con, mlx->win, &mlx->mouse_x, &mlx->mouse_y);
	if (keycode == 65307)
		close_window(mlx);
	else if (keycode == 100)
		put_mandelbrot(mlx, mlx->center_x -= 10, mlx->center_y, 1);
	else if (keycode == 97)
		put_mandelbrot(mlx, mlx->center_x += 10, mlx->center_y, 1);
	else if (keycode == 115)
		put_mandelbrot(mlx, mlx->center_x, mlx->center_y -= 10, 1);
	else if (keycode == 119)
		put_mandelbrot(mlx, mlx->center_x, mlx->center_y += 10, 1);
	return (0);
}
