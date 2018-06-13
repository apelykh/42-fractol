/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 22:21:02 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 22:21:03 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			close_window(void)
{
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void	change_num_iter(int key, t_fract *prog_data)
{
	t_fparams	*params;
	int			iter_num;

	params = prog_data->fparams;
	if (key == ITER_UP_KEY)
	{
		iter_num = params->max_iter + ITER_STEP;
		params->max_iter = (iter_num < 0) ? 0 : iter_num;
	}
	else if (key == ITER_DOWN_KEY)
	{
		iter_num = params->max_iter - ITER_STEP;
		params->max_iter = (iter_num < 0) ? 0 : iter_num;
	}
	redraw_image(prog_data);
}

int			key_press_event(int key, t_fract *prog_data)
{
	if (key == KEY_EXIT)
		close_window();
	else if ((key >= KEY_NUM_1 && key <= KEY_NUM_7) || key == KEY_NUM_8)
		choose_fractal(key, prog_data);
	else if ((key >= KEY_COLOR_1 && key <= KEY_COLOR_4) || key == KEY_COLOR_5)
		choose_color(key, prog_data);
	else if (key == KEY_SPACE)
		prog_data->is_moving = (prog_data->is_moving == 0) ? 1 : 0;
	else if (key >= KEY_LEFT && key <= KEY_UP)
		move_image(key, prog_data);
	else if (key == ITER_UP_KEY || key == ITER_DOWN_KEY)
		change_num_iter(key, prog_data);
	else if (key == KEY_RESET)
	{
		prog_data->fparams = init_fparams();
		redraw_image(prog_data);
	}
	return (EXIT_SUCCESS);
}

int			mouse_event(int mouse_event, int x, int y, t_fract *prog_data)
{
	int	is_event;

	is_event = 0;
	if (mouse_event == MOUSE_SCROLL_UP)
	{
		change_zoom(prog_data->fparams, ZOOM_OUT_FACTOR, x, y);
		is_event = 1;
	}
	else if (mouse_event == MOUSE_SCROLL_DOWN)
	{
		change_zoom(prog_data->fparams, ZOOM_IN_FACTOR, x, y);
		is_event = 1;
	}
	if (is_event)
		redraw_image(prog_data);
	return (EXIT_SUCCESS);
}

int			mouse_motion_event(int x, int y, t_fract *prog_data)
{
	t_fparams	*params;

	params = prog_data->fparams;
	if (((prog_data->cur_fract == julia) ||
		(prog_data->cur_fract == infin_julia)) &&
		(x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT))
		if (prog_data->is_moving && prog_data->cur_fract != 0)
		{
			params->x_shift = x * params->re_factor + params->min_re;
			params->y_shift = y * params->im_factor + params->min_im;
			redraw_image(prog_data);
		}
	return (EXIT_SUCCESS);
}
