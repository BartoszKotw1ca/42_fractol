/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:35:53 by bkotwica          #+#    #+#             */
/*   Updated: 2024/04/18 18:02:02 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	run_program(int argc, char **argv)
{
	int	mandel;
	int	julia;

	julia = 74;
	mandel = 77;
	if (argv[1][0] == mandel && argv[1][1] == '\0' && argc == 2)
		mandelbrot_program();
	else if (argv[1][0] == julia && argv[1][1] == '\0' && argc == 8)
	{
		if (create_number(argv + 2) == 0 && create_number(argv + 5) == 0)
			exit_message();
		julia_program(create_number(argv + 2), create_number(argv + 5));
	}
	else
		exit_message();
}

int	main(int argc, char **argv)
{
	run_program(argc, argv);
}

//cc main.c mlxlibX/libmlx_Linux.a -lXext -lX11
