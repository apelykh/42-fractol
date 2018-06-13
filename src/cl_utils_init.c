/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:59:24 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 16:59:24 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

static void	cl_buff_alloc(t_cl_data *cl_data)
{
	size_t	buf_size;
	int		status;

	cl_data->params = (cl_double *)malloc(sizeof(cl_double) * NUM_PARAMS);
	buf_size = WIN_HEIGHT * WIN_WIDTH * sizeof(int32_t);
	cl_data->input_buf = clCreateBuffer(cl_data->context, CL_MEM_READ_WRITE,
		buf_size, 0, &status);
	if (!cl_data->input_buf || status != CL_SUCCESS)
		print_fatal("[-] OpenCL can not allocate buffer for pixels\n");
	buf_size = NUM_PARAMS * sizeof(cl_double);
	cl_data->params_buf = clCreateBuffer(cl_data->context, CL_MEM_READ_ONLY,
		buf_size, 0, &status);
	if (!cl_data->params_buf || status != CL_SUCCESS)
		print_fatal("[-] OpenCL can not allocate buffer for kernel params\n");
}

t_cl_data	*cl_init_model(t_fract *prog_data)
{
	t_cl_data	*cl_data;
	int			status;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	cl_data = (t_cl_data*)malloc(sizeof(t_cl_data));
	cl_data->image = (cl_char*)mlx_get_data_addr(
		prog_data->image, &bits_per_pixel, &size_line, &endian);
	status = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &(cl_data->device), 0);
	if (status != CL_SUCCESS)
		print_fatal("[-] Can not get GPU devise\n");
	cl_data->context = clCreateContext(0, 1, &cl_data->device, 0, 0, &status);
	if (!cl_data->context || status != CL_SUCCESS)
		print_fatal("[-] Can not create context\n");
	cl_data->queue = clCreateCommandQueue(cl_data->context, cl_data->device, 0,
		&status);
	if (!cl_data->queue || status != CL_SUCCESS)
		print_fatal("[-] Can not create command queue\n");
	cl_buff_alloc(cl_data);
	return (cl_data);
}
