/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/16 14:26:52 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

double	myabs(double number)
{
	if (number < 0)
		return (-1 * number);
	return (number);
}

double	if_in_set(double number)
{
	if (myabs(number) < 2)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_fract *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	closee(int keycode, t_fract *vars)
{
	mlx_destroy_window(vars->con, vars->win);
	return (0);
}

int	key_hook(int keycode, t_fract *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->con, mlx->win);
		mlx_destroy_display(mlx->con);
		free(mlx->con);
		//free(mlx->addr);
		//free(mlx->img);
		printf("ESC\n");
		exit (0);
	}
	return (0);
}

void draw_mandelbrot(t_fract *mlx)
{
    t_point pixel, c, z;
    t_point z_squared;
    int max_iter = 1000;
    int iter;
    int colors[10] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0xC0C0C0, 0x808080, 0x800000};

    for (pixel.z = 0; pixel.z < HEIGHT; pixel.z++)
    {
        for (pixel.i = 0; pixel.i < WIDTH; pixel.i++)
        {
            c.i = (pixel.i - WIDTH / 2.0) * 4.0 / WIDTH;
            c.z = (pixel.z - HEIGHT / 2.0) * 4.0 / HEIGHT;
            z = c;
            z_squared.i = z.i * z.i;
            z_squared.z = z.z * z.z;

            for (iter = 0; iter < max_iter && ((z_squared.i + z_squared.z) <= 4.0); iter++)
            {
                z.z = 2.0 * z.i * z.z + c.z;
                z.i = z_squared.i - z_squared.z + c.i;
                z_squared.i = z.i * z.i;
                z_squared.z = z.z * z.z;
            }

            if (iter == max_iter)
                my_mlx_pixel_put(mlx, pixel.i, pixel.z, 0x00FF00); // black for points inside Mandelbrot set
            else
                my_mlx_pixel_put(mlx, pixel.i, pixel.z, colors[iter % 10]); // white for points outside the set
        }
    }
}

int	main(void)
{
	t_fract	mlx;

	mlx.con = mlx_init();
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractal");
	mlx.img = mlx_new_image(mlx.con, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
		&mlx.line_length, &mlx.endian);
	draw_mandelbrot(&mlx);
	//my_mlx_pixel_put(&mlx, WIDTH / 2, HEIGHT / 2, 0x00FF0000);

	mlx_put_image_to_window(mlx.con, mlx.win,
		mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.con);
	// int	i = 20;
	// int j = 0;
	// while (i++ < 200)
	// {
	// 	j = 20;
	// 	while (j++ < 100)
	// 		mlx_pixel_put(mlx_connection, win, j, i,  0xff0000);
	// }
	//printf("%f", if_in_set(-1.99999));
	// t_fract	point;
	// t_fract	set;
	// double	tmp;

	// point.i = 0.4;
	// point.z = 0.25;

	// set.i = 0;
	// set.z = 0;

	// i = 0;
	// while (i ++ < 42)
	// {
	// 	printf("%f %f \n", set.z, set.i);
	// 	tmp = (set.z * set.z) - (set.i * set.i);
	// 	set.i = 2 * set.i * set.z + point.i;
	// 	set.z = tmp + point.z;
	// }
}

//cc main.c mlxlibX/libmlx_Linux.a -lXext -lX11
