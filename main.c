/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/11 09:23:37 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx_connection;
	void	*win;
	//t_fract	img;

	mlx_connection = mlx_init();
	win = mlx_new_window(mlx_connection, 500, 500, "New window");
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
			mlx_pixel_put(mlx_connection, win, j, i,  0xff0000);
	}
	mlx_loop(mlx_connection);
	mlx_destroy_display(mlx_connection); // to correct exit to program we have to clode that connecion
	free(mlx_connection); // we have to free it bcs it is malloced in mlx_init
}
