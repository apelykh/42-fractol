/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:18:30 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 16:18:31 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

t_fparams	*init_fparams(void)
{
	t_fparams	*fparams;

	fparams = (t_fparams*)malloc(sizeof(t_fparams));
	fparams->zoom = 0.001;
	fparams->zoom_factor = 1;
	fparams->min_re = -2.0;
	fparams->max_re = 2;
	fparams->min_im = 2;
	fparams->max_im = -2;
	fparams->re_factor = (fparams->max_re - fparams->min_re) / (WIN_WIDTH - 1);
	fparams->im_factor = (fparams->max_im - fparams->min_im) / (WIN_HEIGHT - 1);
	fparams->base_color = COLOR_1;
	fparams->max_iter = MAX_ITER;
	return (fparams);
}

t_fract		*prog_data_init(void)
{
	t_fract *prog_data;

	prog_data = (t_fract*)malloc(sizeof(t_fract));
	prog_data->mlx = mlx_init();
	if (!prog_data->mlx)
		print_fatal("[-] MLX init error\n");
	prog_data->win = mlx_new_window(prog_data->mlx, WIN_WIDTH, WIN_HEIGHT,
		"fractol / apelykh");
	prog_data->image = mlx_new_image(prog_data->mlx, WIN_WIDTH, WIN_HEIGHT);
	prog_data->cl_data = cl_init_model(prog_data);
	prog_data->fparams = init_fparams();
	prog_data->is_moving = 1;
	return (prog_data);
}
