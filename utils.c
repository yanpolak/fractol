/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:12:53 by ymarival          #+#    #+#             */
/*   Updated: 2023/03/02 21:24:18 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

void	write_help(void)
{
	ft_putsr_fd("usage: fractol type [re] [im]\n", 1);
	exit(0);
}

void	write_types(void)
{
	ft_putsr_fd("supported types:\njulia\nmandelbrot\nburning ship\n", 1);
	exit(0);
}

void	free_depth(t_fractol *fractol)
{
	size_t	w;

	if (!fractol->depth)
		return ;
	w = 0;
	while (w < WIDTH)
	{
		free(fractol->depth[w]);
		++w;
	}
	free(fractol->depth);
}

int	free_all(t_fractol *fractol)
{
	free_depth(fractol);
	mlx_destroy_image(fractol->mlx->mlx, fractol->mlx->img);
	mlx_destroy_window(fractol->mlx->mlx, fractol->mlx->win);
	free(fractol->mlx);
	free(fractol);
	exit(0);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
