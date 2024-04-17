/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/17 14:28:46 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_fract *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	close_window(t_fract *mlx)
{
	mlx_destroy_window(mlx->con, mlx->win);
	mlx_destroy_display(mlx->con);
	free(mlx->con);
	//free(mlx->addr);
	//free(mlx->img);
	exit (0);
}

// In an RGB color, the value is usually a 24-bit number where:
// 	The 8 least significant bits (rightmost) represent the blue component.
// 	The next 8 bits represent the green component.
// 	The 8 most significant bits (leftmost) represent the red component.
// 	color = red | (green << 8) | (blue << 16)
// int a = 60;    /* 60 = 0011 1100 */
// int b = 13;    /* 13 = 0000 1101 */
// result = a | b; /* result = 61 = 0011 1101 */

void draw_mandelbrot(t_fract *mlx, int x, int y)
{
	t_point pixel, c, z, z_squared;

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
			c.z = (pixel.z + y- HEIGHT) * (4.0 / HEIGHT) * mlx->zoom;
			z = c;
			z_squared.i = z.i * z.i;
			z_squared.z = z.z * z.z;
			mlx-> i = 0;
			while (mlx->i < mlx->max_iter && ((z_squared.i + z_squared.z) <= 4.0))
			{
				z.z = 2.0 * z.i * z.z + c.z;
				z.i = z_squared.i - z_squared.z + c.i;
				z_squared.i = z.i * z.i;
				z_squared.z = z.z * z.z;
				mlx->i ++;
			}
			if (mlx->i == mlx->max_iter)
				my_mlx_pixel_put(mlx, pixel.i, pixel.z, 0x000000);
			else
				my_mlx_pixel_put(mlx, pixel.i, pixel.z, mlx->colors[mlx->i % 256]);
		}
	}
}


// void	draw_mandelbrot(t_fract *mlx, int x, int y)
// {

// }

void	put_mandelbrot(t_fract *mlx, int x, int y, double zoom)
{
	mlx->zoom /= zoom;
	mlx->img = mlx_new_image(mlx->con, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
		&mlx->line_length, &mlx->endian);
	// mlx_mouse_get_pos(mlx->con, mlx->win, &x, &y);
	draw_mandelbrot(mlx, x, y);
	mlx_put_image_to_window(mlx->con, mlx->win,
		mlx->img, 0, 0);
}
int	key_hook(int keycode, t_fract *mlx)
{
	mlx_mouse_get_pos(mlx->con, mlx->win, &mlx->mouse_x, &mlx->mouse_y);
	if (keycode == 65307)
		close_window(mlx);
	else if (keycode == 49)
		put_mandelbrot(mlx, mlx->mouse_x, mlx->mouse_y, 1.5);
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

void	mandelbrot_program(void)
{
	t_fract	mlx;

	mlx.con = mlx_init();
	mlx.zoom = 1.0;
	mlx.center_x = WIDTH / 2;
	mlx.center_y= HEIGHT / 2;
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractal");
	put_mandelbrot(&mlx, WIDTH / 2, HEIGHT / 2, 1);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_mouse_hook(mlx.win, key_hook, &mlx);
	mlx_loop_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.con);
}

void	check_data(int argc, char **argv)
{
	int	Mandel;
	int	Julia;

	Julia = 74;
	Mandel = 77;
	if (argc <= 1 || argc > 2)
	{
		write(1, "!! INVALID DATA !!\n", 20);
		write(1, "M = Mandelbrot set\n", 20);
		write(1, "J = Julia set\n", 14);
		exit (0);
	}
	else if (argv[1][0] == Mandel && argv[1][1] == '\0')
		mandelbrot_program();
}

int	main(int argc, char **argv)
{
	check_data(argc, argv);
}

//cc main.c mlxlibX/libmlx_Linux.a -lXext -lX11
