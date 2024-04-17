/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:32 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/17 13:55:26 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#define HEIGHT 800
#define WIDTH 1000

#include "mlxlibX/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

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
}			t_fract;

typedef struct	s_point
{
	double			i;
	double			z;
}			t_point;

#endif
