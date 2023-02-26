/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:50:34 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/22 17:17:46 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	fractol = parse(argc, argv);
	fractol->mlx = init(fractol);
	draw(fractol);
	mlx_loop(fractol->mlx->mlx);
}

/*La fonction commence par analyser les arguments de la ligne de commande
et initialiser un t_fractal objet avec les valeurs spécifiées.
Il initialise ensuite la bibliothèque graphique et crée une fenêtre
dans laquelle afficher la fractale.  
L'image fractale est générée et affichée
à l'aide de la drawune fonction. 
Enfin, la fonction entre dans la boucle 
d'événements de la bibliothèque graphique, 
qui attend des événements tels qu'une entrée au clavier ou à la souris, 
jusqu'à ce que le programme soit terminé.  Pendant ce temps, 
l'utilisateur peut interagir avec l'image fractale 
à l'aide du clavier ou de la souris.*/