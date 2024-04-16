/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/16 13:25:49 by bkotwica         ###   ########.fr       */
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

int	main(void)
{
	t_fract	mlx;

	mlx.con = mlx_init();
	mlx.win = mlx_new_window(mlx.con, 500, 500, "fractal");
	mlx.img = mlx_new_image(mlx.con, 500, 500);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
		&mlx.line_length, &mlx.endian);
	my_mlx_pixel_put(&mlx, 250, 250, 0x00FF0000);
	mlx_put_image_to_window(mlx.con, mlx.win,
		mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.con);
	//mlx_hook(mlx.win, 2, 1L<<0, closee, &mlx);
	//mlx_loop(mlx.con);
	//img.img = mlx_new_image(mlx, 500, 300);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	/*
	for (int y = 0; y < 500; ++y)
	{
		for (int x = 0; x < 500; ++x)
		{
			mlx_pixel_put(mlx, win, x, y, 0xff0000);
		}
	}
	*/
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
