/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 19:37:43 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/17 19:37:44 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	prepare_kernel_params(cl_double *cl_params, t_fparams *fparams)
{
	cl_params[0] = fparams->max_iter;
	cl_params[1] = fparams->min_re;
	cl_params[2] = fparams->min_im;
	cl_params[3] = fparams->re_factor;
	cl_params[4] = fparams->im_factor;
	cl_params[5] = fparams->base_color;
	cl_params[6] = fparams->x_shift;
	cl_params[7] = fparams->y_shift;
}

void		execute_kernel_program(t_cl_data *cl_data, t_fract *prog_data)
{
	size_t		global_work_size;
	int			status;

	global_work_size = WIN_HEIGHT * WIN_WIDTH;
	status = clEnqueueNDRangeKernel(cl_data->queue, cl_data->kernel, 1, 0,
		&global_work_size, 0, 0, 0, 0);
	if (status != CL_SUCCESS)
		print_fatal("[-] Failed to execute kernel\n");
	clFinish(cl_data->queue);
	status = clEnqueueReadBuffer(cl_data->queue, cl_data->input_buf, CL_TRUE,
		0, WIN_HEIGHT * WIN_WIDTH * sizeof(int32_t), cl_data->image, 0, 0, 0);
	if (status != CL_SUCCESS)
		print_fatal("[-] Failed to read output array\n");
	mlx_put_image_to_window(prog_data->mlx, prog_data->win,
		prog_data->image, 0, 0);
}

static void	create_args_for_kernel(t_cl_data *cl_data, t_fparams *fparams)
{
	cl_double	*cl_params;
	size_t		params_size;
	int			status;

	cl_params = cl_data->params;
	prepare_kernel_params(cl_params, fparams);
	params_size = NUM_PARAMS * sizeof(cl_double);
	status = clEnqueueWriteBuffer(cl_data->queue, cl_data->params_buf,
		CL_TRUE, 0, params_size, cl_params, 0, 0, 0);
	if (status != CL_SUCCESS)
		print_fatal("[-] Failed to write to parameters buffer\n");
	status = clSetKernelArg(cl_data->kernel, 0, sizeof(cl_mem),
		&cl_data->input_buf);
	status |= clSetKernelArg(cl_data->kernel, 1, sizeof(cl_mem),
		&cl_data->params_buf);
	if (status != CL_SUCCESS)
		print_fatal("[-] Failed to set kernel arguments\n");
}

void		redraw_image(t_fract *prog_data)
{
	static enum e_fracts fractal;

	if (fractal != prog_data->cur_fract)
	{
		compile_kernel_program(prog_data->cl_data, prog_data->fract_path);
		fractal = prog_data->cur_fract;
	}
	create_args_for_kernel(prog_data->cl_data, prog_data->fparams);
	execute_kernel_program(prog_data->cl_data, prog_data);
}
