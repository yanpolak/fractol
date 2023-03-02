/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:50:40 by ymarival          #+#    #+#             */
/*   Updated: 2023/03/02 19:18:12 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

/*t_complex structure, qui représente un nombre complexe.
Ce nombre complexe est calculé en fonction de la largeur
et de la hauteur du pixel actuel, ainsi que de la position
et du niveau de zoom de la fenêtre fractale.*/

static	t_complex	get_pos(size_t w, size_t h, t_fractol *fractol)
{
	double	real;
	double	imag;

	real = fractol->corner.real + fractol->zoom * w / WIDTH;
	imag = fractol->corner.imag - fractol->zoom * h / HEIGHT;
	return (init_complex(real, imag));
}

//get_color est responsable de la couleur et la profondeur 
//de l'image de la fractale
static	int	get_color(int depth, int max_depth, int color)
{
	if (depth == max_depth)
		return (create_trgb(0, 0, 0, 0));
	else
		return (create_trgb(0, (depth + color) % 16 * 16, \
					(depth + 3 * color + 4) % 16 * 16, \
					(depth + 7 * color + 8) % 16 * 16));
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
//paint est responsable du rendu de l'image fractale

void	paint(t_fractol *fractol)
{
	size_t	w;
	size_t	h;

	w = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			my_mlx_pixel_put(fractol->mlx, w, HEIGHT - h - 1, \
			get_color(fractol->depth[w][h], MAX_ITERS, fractol->color));
			++h;
		}
			++w;
	}
	mlx_put_image_to_window(fractol->mlx->mlx, fractol->mlx->win, \
							fractol->mlx->img, 0, 0);
}

/*Cette fonction draw génère une carte de profondeur pour la fractale,
puis peint la fractale sur la fenêtre.*/

void	draw(t_fractol *fractol)
{
	size_t	w;
	size_t	h;

	free_depth(fractol);
	fractol->depth = malloc(WIDTH * sizeof(int *));
	if (!fractol->depth)
		exit (1);
	w = 0;
	while (w < WIDTH)
	{
		fractol->depth[w] = malloc(HEIGHT * sizeof(int));
		if (!fractol->depth[w])
			exit (1);
		h = 0;
		while (h < HEIGHT)
		{
			fractol->depth[w][h] = fractol->formula(get_pos(w, h, fractol), \
									fractol);
			++h;
		}
	++w;
	}
	paint(fractol);
}
