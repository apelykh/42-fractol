/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:48:51 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/16 13:48:52 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <limits.h>

static void	choose_other_fractals(int key, t_fract *prog_data)
{
	if (key == INFIN_MAN_KEY)
	{
		prog_data->cur_fract = infin_mandelbrot;
		prog_data->fract_path = INFIN_MAN_KERNEL_PATH;
	}
	else if (key == JULIA_KEY)
	{
		prog_data->cur_fract = julia;
		prog_data->fract_path = JULIA_KERNEL_PATH;
	}
	else if (key == INFIN_JULIA_KEY)
	{
		prog_data->cur_fract = infin_julia;
		prog_data->fract_path = INFIN_JUL_KERNEL_PATH;
	}
	else if (key == BURNING_SHIP_KEY)
	{
		prog_data->cur_fract = burning_ship;
		prog_data->fract_path = SHIP_KERNEL_PATH;
	}
}

void		choose_fractal(int key, t_fract *prog_data)
{
	if (key == MANDELBROT_KEY)
	{
		prog_data->cur_fract = mandelbrot;
		prog_data->fract_path = MANDELBROT_KERNEL_PATH;
	}
	else if (key == MAN3_KEY)
	{
		prog_data->cur_fract = mandelbrot3;
		prog_data->fract_path = MAN3_KERNEL_PATH;
	}
	else if (key == MAN4_KEY)
	{
		prog_data->cur_fract = mandelbrot4;
		prog_data->fract_path = MAN4_KERNEL_PATH;
	}
	else if (key == MAN5_KEY)
	{
		prog_data->cur_fract = mandelbrot5;
		prog_data->fract_path = MAN5_KERNEL_PATH;
	}
	else
		choose_other_fractals(key, prog_data);
	redraw_image(prog_data);
}

void		choose_color(int key, t_fract *prog_data)
{
	if (key == KEY_COLOR_1)
		prog_data->fparams->base_color = COLOR_1;
	else if (key == KEY_COLOR_2)
		prog_data->fparams->base_color = COLOR_2;
	else if (key == KEY_COLOR_3)
		prog_data->fparams->base_color = COLOR_3;
	else if (key == KEY_COLOR_4)
		prog_data->fparams->base_color = COLOR_4;
	else if (key == KEY_COLOR_5)
		prog_data->fparams->base_color = COLOR_5;
	redraw_image(prog_data);
}

void		move_image(int key, t_fract *prog_data)
{
	double shift;

	shift = 0.5 * prog_data->fparams->zoom_factor;
	if (key == KEY_DOWN || key == KEY_LEFT)
		shift = -1 * shift;
	if (key == KEY_UP || key == KEY_DOWN)
	{
		prog_data->fparams->min_im += shift;
		prog_data->fparams->max_im += shift;
	}
	else if (key == KEY_RIGHT || key == KEY_LEFT)
	{
		prog_data->fparams->min_re += shift;
		prog_data->fparams->max_re += shift;
	}
	prog_data->fparams->re_factor = (prog_data->fparams->max_re -
		prog_data->fparams->min_re) / (WIN_WIDTH - 1);
	prog_data->fparams->im_factor = (prog_data->fparams->max_im -
		prog_data->fparams->min_im) / (WIN_HEIGHT - 1);
	redraw_image(prog_data);
}

void		change_zoom(t_fparams *fparams, double zoom, int x, int y)
{
	double dx;
	double dy;
	double rev_zoom;

	dx = x * fparams->re_factor + fparams->min_re;
	dy = y * fparams->im_factor + fparams->min_im;
	fparams->zoom = zoom;
	if (fparams->zoom_factor > LLONG_MIN && fparams->zoom_factor < LLONG_MAX)
		fparams->zoom_factor *= zoom;
	rev_zoom = 1 - fparams->zoom;
	fparams->min_im = fparams->min_im * fparams->zoom + (dy * rev_zoom);
	fparams->max_im = fparams->max_im * fparams->zoom + (dy * rev_zoom);
	fparams->min_re = fparams->min_re * fparams->zoom + (dx * rev_zoom);
	fparams->max_re = fparams->max_re * fparams->zoom + (dx * rev_zoom);
	fparams->re_factor = (fparams->max_re - fparams->min_re) / (WIN_WIDTH - 1);
	fparams->im_factor = (fparams->max_im - fparams->min_im) /
		(WIN_HEIGHT - 1);
}
