/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:50:51 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/16 15:50:52 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__kernel void	computing_set(__global int *pixels, __constant double *params)
{
	int		max_iter	= params[0];
	double	min_re		= params[1];
	double	min_im		= params[2];
	double	re_factor	= params[3];
	double	im_factor	= params[4];
	int		base_color	= params[5];
	double	x_shift		= params[6];
	double	y_shift		= params[7];

	uint x = get_global_id(0) % 1280;
	uint y = get_global_id(0) / 1280;

	double2  z;
	z.x = x * re_factor + min_re;
	z.y = y * im_factor + min_im;

	double2  c;
	c.x = x_shift;
	c.y = y_shift;

	char	is_inside;
	double2	z_sqr;
	int		iter;

	is_inside = 0;
	for (iter = 0; iter < max_iter; ++iter)
	{
		z_sqr = z * z;
		if ((z_sqr.x + z_sqr.y) > 4)
		{
			is_inside = 1;
			break ;
		}
		z.y = 2 * z.x * z.y + c.y;
		z.x = z_sqr.x - z_sqr.y + c.x;
	}
	if (is_inside == 0)
		pixels[get_global_id(0)] = 0x0d0d0d;
	else
		pixels[get_global_id(0)] = (iter * base_color) & 0x00ffffff;
}
