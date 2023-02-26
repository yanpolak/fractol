/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:39:45 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/24 17:20:18 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

int	julia(t_complex pos, t_fractol *fractol)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		real_temp;

	i = 0;
	z = pos;
	c = fractol->c;
	while (i < MAX_ITERS && (z.real * z.real + z.imag * z.imag) < 4)
	{
		real_temp = z.real;
		z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
		z.imag = (2 * real_temp * z.imag) + c.imag;
		i++;
	}
	return (i);
}

int	mandelbrot(t_complex pos, t_fractol *fractol)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		real_temp;

	i = 0;
	z = init_complex(0, 0);
	c = pos;
	while (i < MAX_ITERS && (z.real * z.real + z.imag * z.imag) < 4)
	{
	real_temp = z.real;
		z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
		z.imag = (2 * real_temp * z.imag) + c.imag;
		i++;
	}
	return (i);
}

int	burning_ship(t_complex pos, t_fractol *fractol)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		real_temp;

	i = 0;
	z = init_complex(0, 0);
	c = pos;
	while (i < MAX_ITERS && (z.real * z.real + z.imag * z.imag) < 4)
	{
		real_temp = z.real;
		z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
		z.imag = fabs(2 * real_temp * z.imag) + c.imag;
		i++;
	}
	return (i);
}
