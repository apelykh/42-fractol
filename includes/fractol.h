/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:01:38 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/15 15:01:39 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __OSXSIERRA__
#  include "../mlx_10.12/mlx.h"
# else
#  include "../mlx_10.11/mlx.h"
# endif

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

# define NUM_PARAMS				8
# define KERNEL_SRC_BUF_SIZE 	10000

# define MANDELBROT_KERNEL_PATH	"cl_kernels/mandelbrot.cl"
# define JULIA_KERNEL_PATH		"cl_kernels/julia.cl"
# define SHIP_KERNEL_PATH		"cl_kernels/burning_ship.cl"
# define MAN3_KERNEL_PATH		"cl_kernels/mandelbrot3.cl"
# define MAN4_KERNEL_PATH		"cl_kernels/mandelbrot4.cl"
# define MAN5_KERNEL_PATH		"cl_kernels/mandelbrot5.cl"
# define INFIN_MAN_KERNEL_PATH	"cl_kernels/infin_mandelbrot.cl"
# define INFIN_JUL_KERNEL_PATH	"cl_kernels/infin_julia.cl"

# define COLOR_1				0x010203
# define COLOR_2				0x100110
# define COLOR_3				0x00000F
# define COLOR_4				0x050505
# define COLOR_5				0xF8B1FF

/*
** Farctal parameters
*/
# define WIN_HEIGHT				1280
# define WIN_WIDTH				1280
# define MAX_ITER				800
# define ITER_STEP				50
# define ZOOM_IN_FACTOR			1.1
# define ZOOM_OUT_FACTOR		0.9

/*
** Input event masks
*/
# define KEY_PRESS_MASK			(1L<<0)
# define BUTTON_MOTION_MASK		(1L<<13)
# define STRUCT_NOTIFY_MASK		(1L<<17)

/*
** Event names
*/
# define KEY_PRESS				2
# define MOTION_NOTIFY			6
# define DESTROY_NOTIFY			17

/*
** Key codes
*/
# define KEY_NUM_1				83
# define KEY_NUM_2				84
# define KEY_NUM_3				85
# define KEY_NUM_4				86
# define KEY_NUM_5				87
# define KEY_NUM_6				88
# define KEY_NUM_7				89
# define KEY_NUM_8				91
# define KEY_EXIT				53
# define KEY_CLOSE_WIN			65307
# define KEY_SPACE				49
# define KEY_RESET				15
# define ITER_UP_KEY			69
# define ITER_DOWN_KEY			78
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_DOWN				125
# define KEY_UP					126
# define KEY_COLOR_1			18
# define KEY_COLOR_2			19
# define KEY_COLOR_3			20
# define KEY_COLOR_4			21
# define KEY_COLOR_5			23
# define MOUSE_SCROLL_UP		5
# define MOUSE_SCROLL_DOWN		4

# define MANDELBROT_KEY			KEY_NUM_1
# define JULIA_KEY				KEY_NUM_2
# define BURNING_SHIP_KEY		KEY_NUM_3
# define MAN3_KEY				KEY_NUM_4
# define MAN4_KEY				KEY_NUM_5
# define MAN5_KEY				KEY_NUM_6
# define INFIN_MAN_KEY			KEY_NUM_7
# define INFIN_JULIA_KEY		KEY_NUM_8

/*
** input_buf: OpenCL memory buffer that holds information about input pixels
** params: array of cl_double, kernel parameters
** params_buf: OpenCL memory buffer that holds kernel parameters
*/
typedef struct			s_cl_data
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_char				*image;
	cl_mem				input_buf;
	cl_double			*params;
	cl_mem				params_buf;
}						t_cl_data;

enum	e_fracts
{
	none = 0,
	mandelbrot,
	julia,
	burning_ship,
	mandelbrot3,
	mandelbrot4,
	mandelbrot5,
	infin_mandelbrot,
	infin_julia,
};

typedef struct			s_fparams
{
	double				zoom;
	double				zoom_factor;
	double				min_re;
	double				max_re;
	double				min_im;
	double				max_im;
	double				re_factor;
	double				im_factor;
	int					base_color;
	int					max_iter;
	double				x_shift;
	double				y_shift;
}						t_fparams;

typedef struct			s_fract
{
	void				*mlx;
	void				*win;
	void				*image;
	t_cl_data			*cl_data;
	t_fparams			*fparams;
	char				*fract_path;
	int					is_moving;
	size_t				cur_fract;
}						t_fract;

/*
** src/init.c
*/
t_fparams				*init_fparams(void);
t_fract					*prog_data_init(void);

/*
** src/cl_utils_init.c
*/
t_cl_data				*cl_init_model(t_fract *prog_data);

/*
** src/cl_utils_compile.c
*/
void					compile_kernel_program(t_cl_data *cl_data,
							const char *filepath);

/*
** src/cl_utils_exec.c
*/
void					execute_kernel_program(t_cl_data *cl_data,
							t_fract *prog_data);
void					redraw_image(t_fract *prog_data);

/*
** src/control_events.c
*/
int						close_window(void);
int						key_press_event(int key, t_fract *prog_data);
int						mouse_event(int mouse_event, int x, int y,
							t_fract *prog_data);
int						mouse_motion_event(int x, int y, t_fract *prog_data);

/*
** src/params_modification.c
*/
void					choose_fractal(int key, t_fract *prog_data);
void					choose_color(int key, t_fract *prog_data);
void					move_image(int key, t_fract *prog_data);
void					change_zoom(t_fparams *fparams, double zoom_factor,
							int x, int y);

/*
** src/main.c
*/
void					print_fatal(char *err_msg);

#endif
