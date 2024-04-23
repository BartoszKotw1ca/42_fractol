/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:45:21 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/23 10:44:32 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// This function calculates the Julia set for a given pixel.
// It uses the complex plane and the formula for the Julia set to 
// calculate the color of each pixel.
// The formula for the Julia set is z = z^2 + c, where z and c 
// are complex numbers.
// The function iterates this formula until the magnitude of z exceeds 
// 4.0 or the maximum number of iterations is reached.
void	calculation_julia(t_fract *mlx, t_point pixel, int x, int y)
{
	t_point	z;
	t_point	z_squared;

	z.i = (pixel.i + x - WIDTH) * (4.0 / WIDTH) * mlx->zoom;
	z.z = (pixel.z + y - HEIGHT) * (4.0 / HEIGHT) * mlx->zoom;
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

// This function draws the Julia set on the screen.
// It iterates over each pixel on the screen and 
// calculates the color of the pixel using the calculation_julia function.
// If the pixel is in the Julia set (i.e., the number of 
// iterations reached the maximum), it is colored black.
// Otherwise, it is colored based on the number of iterations 
// it took to escape the set.
void	draw_julia(t_fract *mlx, int x, int y)
{
	t_point	pixel;

	mlx->i = -1;
	mlx->max_iter = 1000;
	pixel.z = -1;
	while (mlx->i++ < 256)
		mlx->colors[mlx->i] = (mlx->i * 10 << 16);
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

// This function updates the Julia set image with a new zoom level.
// It creates a new image, draws the Julia set on the image with 
// the new zoom level, and then puts the image on the window.
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

// This function handles mouse events for the Julia set.
// It updates the image based on the mouse position and 
// zooms in or out based on the mouse wheel.
// If the mouse wheel is scrolled up (keycode 4), it zooms in.
// If the mouse wheel is scrolled down (keycode 5), it zooms out.
int	mouse_hook_julia(int keycode, int x, int y, t_fract *mlx)
{
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (keycode == 4)
		destroy_and_put_julia(mlx, mlx->mouse_x, mlx->mouse_y, 1.5);
	else if (keycode == 5)
		destroy_and_put_julia(mlx, mlx->mouse_x, mlx->mouse_y, 0.5);
	return (0);
}

// This function handles keyboard events for the Julia set.
// It allows the user to move the image using the 
// keyboard and to close the window.
// If the escape key (keycode 65307) is pressed, it closes the window.
// If the 'd' key (keycode 100) is pressed, it moves the image to the right.
// If the 'a' key (keycode 97) is pressed, it moves the image to the left.
// If the 's' key (keycode 115) is pressed, it moves the image down.
// If the 'w' key (keycode 119) is pressed, it moves the image up.
int	key_hook_julia(int keycode, t_fract *mlx)
{
	mlx_mouse_get_pos(mlx->con, mlx->win, &(mlx->mouse_x), &(mlx->mouse_y));
	if (keycode == 65307)
		close_window(mlx);
	if (keycode == 100)
		destroy_and_put_julia(mlx, mlx->center_x -= 10, mlx->center_y, 1);
	else if (keycode == 97)
		destroy_and_put_julia(mlx, mlx->center_x += 10, mlx->center_y, 1);
	else if (keycode == 115)
		destroy_and_put_julia(mlx, mlx->center_x, mlx->center_y -= 10, 1);
	else if (keycode == 119)
		destroy_and_put_julia(mlx, mlx->center_x, mlx->center_y += 10, 1);
	return (0);
}
