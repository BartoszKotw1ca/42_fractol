/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:00:21 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/24 13:02:06 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// This function runs the appropriate fractal program based
//  on the command line arguments.
// If the first argument is 'M' (ASCII 77), it runs the Mandelbrot program.
// If the first argument is 'J' (ASCII 74), it runs the 
// Julia program with the parameters provided in the next six arguments.

void	run_program(int argc, char **argv)
{
	int	mandel;
	int	julia;

	julia = 74;
	mandel = 77;
	if (argc == 2 && argv[1][0] == mandel && argv[1][1] == '\0')
		mandelbrot_program();
	else if ((argc == 8 && argv[1][0] == julia && argv[1][1] == '\0')
		&& (if_sign(argv[2]) && if_num(argv[3]) && if_num(argv[4]))
		&& (if_sign(argv[5]) && if_num(argv[6]) && if_num(argv[7])))
	{
		if (create_number(argv + 2) == 0 && create_number(argv + 5) == 0)
			exit_message();
		julia_program(create_number(argv + 2), create_number(argv + 5));
	}
	else
		exit_message();
}

int	if_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i ++;
	}
	return (1);
}

int	if_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 43 && str[i] != 45)
		{
			return (0);
		}
		i ++;
	}
	if (i != 1)
		return (0);
	return (1);
}

double	create_number(char	**argv)
{
	double	number;
	int		tmp;
	int		dzielnik;

	dzielnik = 1;
	number = ft_atoi(argv[2]);
	tmp = number;
	while (tmp)
	{
		tmp /= 10;
		dzielnik *= 10;
	}
	if (str_len(argv[2]) / dzielnik != 0)
		number /= str_len(argv[2]);
	else
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
