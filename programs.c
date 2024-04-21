/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:51:43 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/20 10:48:39 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	put_julia(&mlx, WIDTH / 2, HEIGHT / 2, 1);
	mlx_hook(mlx.win, 17, 0L, mlx_loop_end, mlx.con);
	mlx_mouse_hook(mlx.win, mouse_hook_julia, &mlx);
	mlx_key_hook(mlx.win, key_hook_julia, &mlx);
	mlx_loop(mlx.con);
	close_window(&mlx);
}

void	mandelbrot_program(void)
{
	t_fract	mlx;

	mlx.con = mlx_init();
	mlx.zoom = 1.0;
	mlx.center_x = WIDTH / 2;
	mlx.center_y = HEIGHT / 2;
	mlx.win = mlx_new_window(mlx.con, WIDTH, HEIGHT, "fractal");
	put_mandelbrot(&mlx, WIDTH / 2, HEIGHT / 2, 1);
	mlx_hook(mlx.win, 17, 0L, mlx_loop_end, mlx.con);
	mlx_mouse_hook(mlx.win, mouse_hook_mandelbrot, &mlx);
	mlx_key_hook(mlx.win, key_hook_mandel, &mlx);
	mlx_loop(mlx.con);
	close_window(&mlx);
}

int	str_len(char *str)
{
	int	i;
	int	number;

	number = 1;
	i = 0;
	while (str[i ++])
		number *= 10;
	return (number);
}
