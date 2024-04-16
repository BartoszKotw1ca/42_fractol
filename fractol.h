/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:32 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/15 16:04:53 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include "mlxlibX/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct s_img
{
	 
}

typedef struct s_fractal
{
	void	*mlx_connection;
	void	*mlx_window;
}

typedef struct	s_fract
{
	double			i;
	double			z;
	//struct s_fract	*next;
	// struct s_fract	*prev;
}			t_fract;

#endif
