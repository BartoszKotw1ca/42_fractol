/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:32 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/16 15:39:11 by bkotwica         ###   ########.fr       */
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
}			t_fract;

typedef struct	s_point
{
	double			i;
	double			z;
	//struct s_fract	*next;
	// struct s_fract	*prev;
}			t_point;

#endif
