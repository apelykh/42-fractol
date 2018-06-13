/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils_compile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 19:17:08 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 19:17:09 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

static void	create_kernel_from_src(t_cl_data *cl_data, const char *filepath)
{
	FILE	*kernel_file;
	size_t	kernel_size;
	char	*kernel;
	int		status;

	if (!(kernel = (char*)malloc(sizeof(char) * KERNEL_SRC_BUF_SIZE)))
		print_fatal("[-] Not enough memory for kernel\n");
	if (!(kernel_file = fopen(filepath, "r")))
		print_fatal("[-] Can not open kernel source\n");
	if ((kernel_size = fread(kernel, 1, KERNEL_SRC_BUF_SIZE, kernel_file)) < 1)
		print_fatal("[-] Kernel source corrupted\n");
	kernel[kernel_size] = '\0';
	fclose(kernel_file);
	cl_data->program = clCreateProgramWithSource(cl_data->context, 1,
		(const char **)&kernel, 0, &status);
	if (!cl_data->program || status != CL_SUCCESS)
		print_fatal("[-] Failed to cleare kernel program\n");
	free(kernel);
}

void		compile_kernel_program(t_cl_data *cl_data, const char *filepath)
{
	int		status;
	size_t	len;
	char	build_info[2048];

	create_kernel_from_src(cl_data, filepath);
	status = clBuildProgram(cl_data->program, 1, &(cl_data->device), 0, 0, 0);
	if (status != CL_SUCCESS)
	{
		printf("[-] Failed to build program executable\n");
		clGetProgramBuildInfo(cl_data->program, cl_data->device,
			CL_PROGRAM_BUILD_LOG, sizeof(build_info), build_info, &len);
		print_fatal(build_info);
	}
	cl_data->kernel = clCreateKernel(cl_data->program, "computing_set",
		&status);
	if (!cl_data->kernel || status != CL_SUCCESS)
		print_fatal("[-] Failed to create compute kernel!\n");
}
