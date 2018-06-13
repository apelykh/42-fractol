/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:09:16 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 15:09:16 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <stdio.h>

void		print_fatal(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

static void	print_usage(int argc, int wrong_arg)
{
	if (argc != 2 || wrong_arg)
	{
		printf("\nUsage: ./fractol fractal_id\n");
		printf("\nAvaliable fractals:\n");
		printf("\t1. Mandelbrot\n");
		printf("\t2. Julia\n");
		printf("\t3. Burning Ship\n");
		printf("\t4. Mandelbrot^3\n");
		printf("\t5. Mandelbrot^4\n");
		printf("\t6. Mandelbrot^5\n");
		printf("\t7. Infinite Mandelbrot\n");
		printf("\t8. Infinite Julia\n");
		exit(EXIT_FAILURE);
	}
}

static void	parse_input(int argc, char **argv, t_fract *prog_data)
{
	int	wrong_arg;

	wrong_arg = 0;
	if (argc == 2 && argv[1])
	{
		if (!ft_strcmp("1", argv[1]))
			key_press_event(MANDELBROT_KEY, prog_data);
		else if (!ft_strcmp("2", argv[1]))
			key_press_event(JULIA_KEY, prog_data);
		else if (!ft_strcmp("3", argv[1]))
			key_press_event(BURNING_SHIP_KEY, prog_data);
		else if (!ft_strcmp("4", argv[1]))
			key_press_event(MAN3_KEY, prog_data);
		else if (!ft_strcmp("5", argv[1]))
			key_press_event(MAN4_KEY, prog_data);
		else if (!ft_strcmp("6", argv[1]))
			key_press_event(MAN5_KEY, prog_data);
		else if (!ft_strcmp("7", argv[1]))
			key_press_event(INFIN_MAN_KEY, prog_data);
		else if (!ft_strcmp("8", argv[1]))
			key_press_event(INFIN_JULIA_KEY, prog_data);
		else
			wrong_arg = 1;
	}
	print_usage(argc, wrong_arg);
}

int			main(int argc, char **argv)
{
	t_fract *prog_data;

	prog_data = prog_data_init();
	parse_input(argc, argv, prog_data);
	mlx_hook(prog_data->win, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK,
		close_window, NULL);
	mlx_hook(prog_data->win, KEY_PRESS, KEY_PRESS_MASK,
		key_press_event, (void*)prog_data);
	mlx_hook(prog_data->win, MOTION_NOTIFY, BUTTON_MOTION_MASK,
		mouse_motion_event, (void*)prog_data);
	mlx_mouse_hook(prog_data->win, mouse_event, (void*)prog_data);
	mlx_loop(prog_data->mlx);
	return (0);
}
