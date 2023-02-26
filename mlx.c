/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:34:34 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/23 13:07:51 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "keys.h"
/*
static	int	mouse_handler(int button, int x, int y, void *param)
{
	t_fractol	*frac;
	t_complex	p;

	frac = param;
	p = init_complex(frac->corner.real + frac->zoom * x / WIDTH, \
						frac->corner.imag - frac->zoom * y / HEIGHT);
	if (button == SCROLL_UP)
	{
		frac->zoom *= ZOOM_STEP;
		frac->corner.real = (frac->corner.real - p.real) * ZOOM_STEP + p.real;
		frac->corner.imag = (frac->corner.imag - p.imag) * ZOOM_STEP + p.imag;
	}
	else if (button == SCROLL_DOWN)
	{
		frac->zoom /= ZOOM_STEP;
		frac->corner.real = (frac->corner.real - p.real) * ZOOM_STEP + p.real;
		frac->corner.imag = (frac->corner.imag - p.imag) * ZOOM_STEP + p.imag;
	}
	else
		return (0);
	draw(frac);
	return (0);
}
*/

static int mouse_handler(int button, int x, int y, void *param)
{
    t_fractol *frac = (t_fractol *)param;

    double mouse_real = frac->corner.real + frac->zoom * x / WIDTH;
    double mouse_imag = frac->corner.imag - frac->zoom * y / HEIGHT;

    if (button == SCROLL_UP)
    {
        double zoom_factor = 1.0 / ZOOM_STEP;
        frac->zoom *= zoom_factor;
        frac->corner.real = mouse_real - frac->zoom * x / WIDTH;
        frac->corner.imag = mouse_imag + frac->zoom * y / HEIGHT;
    }
    else if (button == SCROLL_DOWN)
    {
        frac->zoom *= ZOOM_STEP;
        frac->corner.real = mouse_real - frac->zoom * x / WIDTH;
        frac->corner.imag = mouse_imag + frac->zoom * y / HEIGHT;
    }
    else
    {
        return (0);
    }

    draw(frac);

    return (0);
}

static int	key_handler2(int key_code, t_fractol *frac)
{
	if (key_code == W)
	frac->c.imag /= 0.9;
	else if (key_code == S)
	frac->c.imag *= 0.9;
	else if (key_code == D)
	frac->c.real /= 0.9;
	else if (key_code == A)
	frac->c.real *= 0.9;
	else
		return (0);
	draw(frac);
	return (0);
}

static int	key_handler(int key_code, t_fractol *param)
{
	t_fractol	*frac;

	frac = param;
	if (key_code == ESC)
		free_all(frac);
	else if (key_code == C)
	{
		frac->color += 2;
		paint(frac);
		return (0);
	}
	else if (key_code == UP)
		frac->corner.imag += frac->zoom / MOVE_STEP;
	else if (key_code == DOWN)
		frac->corner.imag -= frac->zoom / MOVE_STEP;
	else if (key_code == RIGHT)
		frac->corner.real += frac->zoom / MOVE_STEP;
	else if (key_code == LEFT)
		frac->corner.real -= frac->zoom / MOVE_STEP;
	else
		return (key_handler2(key_code, frac));
	draw(frac);
	return (0);
}

t_mlx	*init(t_fractol *fractol)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		exit(1);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fractol");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
				&mlx->line_length, &mlx->endian);
	mlx_mouse_hook(mlx->win, mouse_handler, fractol);
	mlx_key_hook(mlx->win, key_handler, fractol);
	mlx_hook(mlx->win, 17, 0, free_all, fractol);
	return (mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
