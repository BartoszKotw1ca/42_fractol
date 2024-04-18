/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:45:57 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/18 12:26:45 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fract *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//free(mlx->addr);
//free(mlx->img);
void	close_window(t_fract *mlx)
{
	mlx_destroy_window(mlx->con, mlx->win);
	mlx_destroy_display(mlx->con);
	free(mlx->con);
	exit (0);
}

double	create_number(char	**argv)
{
	double	number;
	int		tmp;
	int		dzielnik;

	dzielnik = 1;
	number = ft_atoi(argv[2]);
	if (!number)
		return (0);
	tmp = number;
	while (tmp)
	{
		tmp /= 10;
		dzielnik *= 10;
	}
	number /= dzielnik;
	number += ft_atoi(argv[1]);
	if (argv[0][0] == '-' && argv[0][1] == '\0')
		number *= -1;
	else if (argv[0][0] == '+' && argv[0][1] == '\0')
		number *= 1;
	else
		return (0);
	return (number);
}

int	ft_atoi(const char *nptr)
{
	char	*nr;
	int		i;
	int		sign;
	int		num;

	num = 0;
	sign = 1;
	i = 0;
	nr = (char *) nptr;
	while (nr[i] == 32 || nr[i] == '\r' || nr[i] == '\n'
		|| nr[i] == '\v' || nr[i] == '\f' || nr[i] == '\t')
		i ++;
	if (nr[i] == '-' || nr[i] == '+')
	{
		if (nr[i] == '-')
			sign = -1;
		i ++;
	}
	while (nr[i] <= '9' && nr[i] >= '0')
	{
		num = num * 10 + nr[i] - '0';
		i ++;
	}
	return (sign * num);
}

void	exit_message(void)
{
	write(1, "!! INVALID DATA !!\n", 20);
	write(1, "M = Mandelbrot set\n", 20);
	write(1, "J sign base(before ,) mantisa(after ,) \
sign base(before ,) mantisa(after ,) = Julia set\n", 88);
	write(1, "Everything shoud be splited by spaces!!!\n", 41);
	exit (0);
}
