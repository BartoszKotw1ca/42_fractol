/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/10 12:55:39 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_fract *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*win;
	//t_fract	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "New window");
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
	int	i = 20;
	int j = 0;
	while (i++ < 200)
	{
		j = 20;
		while (j++ < 100)
			mlx_pixel_put(mlx, win, j, i,  0xff0000);
	}
	mlx_loop(mlx);
}
