/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot5.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:48:51 by apelykh           #+#    #+#             */
/*   Updated: 2017/10/16 13:48:52 by apelykh          ###   ########.fr       */
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

	uint x = get_global_id(0) % 1280;
	uint y = get_global_id(0) / 1280;

	double2  c;
	c.x = x * re_factor + min_re;
	c.y = y * im_factor + min_im;
	
	double2	z = c;
	double2	z_sqr;
	double2	z_sqr_sqr;
    double	im_re_sqr;
	char	is_inside;
	int		iter;

	is_inside = 0;
	for (iter = 0; iter < max_iter; ++iter)
	{
        z_sqr = z * z;
        z_sqr_sqr = z_sqr * z_sqr;
        im_re_sqr = z_sqr.x * z_sqr.y;
        if ((z_sqr.x + z_sqr.y) > 4)
        {
            is_inside = 1;
            break ;
        }
        z.y = z.y * (5 * z_sqr_sqr.x - 10 * im_re_sqr + z_sqr_sqr.y) + c.y;
        z.x = z.x * (z_sqr_sqr.x - 10 * im_re_sqr + 5 * z_sqr_sqr.y) + c.x;
    }
	if (is_inside == 0)
		pixels[get_global_id(0)] = 0x0d0d0d;
	else
		pixels[get_global_id(0)] = (iter * base_color) & 0x00ffffff;
}
