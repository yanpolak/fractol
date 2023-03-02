/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:30:36 by ymarival          #+#    #+#             */
/*   Updated: 2023/03/02 18:49:14 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*Cette fonction calcule le dénominateur d'un nombre
donné afin de le convertir en une valeur décimale*/
static double	den(long long n)
{
	double	ans;

	ans = 1;
	while (n)
	{
		n /= 10;
		ans /= 10;
	}
	return (ans);
}

/*le ft_atod La fonction convertit une chaîne en 
un nombre à virgule flottante double
précision en séparant les parties entière et fractionnaire du nombre
et en réduisant la partie fractionnaire à la taille appropriée.*/

static	double	ft_atod(char *s)
{
	size_t		i;
	long long	integ;
	long long	frac;

	if (!s)
		return (0);
	i = 0;
	integ = ft_atol(s + i);
	while (s[i] && s[i] != '.')
		i++;
	if (!s[i])
		return (integ);
	i++;
	frac = ft_atol(s + i);
	return ((double)integ + (double)frac * den(frac));
}

static void	initialize(t_fractol *fractol)
{
	fractol->corner = init_complex(-1, 1);
	fractol->zoom = 2;
	fractol->color = 0;
	fractol->depth = NULL;
}

t_fractol	*parse(int argc, char **argv)
{
	t_fractol	*fractol;

	if (argc < 2 || argc > 4)
		write_help();
	fractol = malloc(sizeof(t_fractol));
	if (!fractol)
		exit(1);
	if (ft_streq(argv[1], "julia"))
		fractol->formula = &julia;
	else if (ft_streq(argv[1], "mandelbrot"))
		fractol->formula = &mandelbrot;
	else if (ft_streq(argv[1], "burning_ship"))
		fractol->formula = &burning_ship;
	else
		write_types();
	if (argc == 2)
	fractol->c = init_complex(-0.81, 0.156);
	else if (argc == 3)
	fractol->c = init_complex(ft_atod(argv[2]), 0);
	else
	fractol->c = init_complex(ft_atod(argv[2]), ft_atod(argv[3]));
	initialize(fractol);
	return (fractol);
}

/*La fonction lit les arguments de la ligne de commande et détermine
le type de fractale à afficher, ainsi que tout autre paramètre
devant être défini pour cette fractale.
Il initialise alors le t_fractal struct et renvoie un pointeur vers celui-ci.
Le reste du programme peut alors utiliser
ce t_fractal struct pour générer l'image fractale.*/