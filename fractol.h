/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:32 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/19 14:58:03 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HEIGHT 800
# define WIDTH 1000

# include "mlxlibX/mlx.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point
{
	double	i;
	double	z;
}			t_point;

typedef struct s_fract
{
	void	*con;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	int		center_x;
	int		center_y;
	int		mouse_x;
	int		mouse_y;
	int		i;
	int		max_iter;
	int		colors[256];
	t_point	c;
}			t_fract;

// Utilis
void	close_window(t_fract *mlx);
void	my_mlx_pixel_put(t_fract *data, int x, int y, int color);
int		ft_atoi(const char *nptr);
double	create_number(char	**argv);
void	exit_message(void);

// Mandelbrot set
void	calculation_mandel(t_fract *mlx, t_point *c);
void	draw_mandelbrot(t_fract *mlx, int x, int y);
void	put_mandelbrot(t_fract *mlx, int x, int y, double zoom);
int		key_hook_mandel(int keycode, t_fract *mlx);
void	mandelbrot_program(void);
int		mouse_hook_mandelbrot(int keycode, int x, int y, t_fract *mlx);

// Julia set
void	calculation_julia(t_fract *mlx, t_point pixel, int x, int y);
void	draw_julia(t_fract *mlx, int x, int y);
void	put_julia(t_fract *mlx, int x, int y, double zoom);
int		key_hook_julia(int keycode, t_fract *mlx);
void	julia_program(double x, double y);
int		mouse_hook_julia(int keycode, int x, int y, t_fract *mlx);

#endif
