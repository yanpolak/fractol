/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:03:03 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/23 18:55:03 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <limits.h>
# include <unistd.h>
# include <mlx.h>
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <math.h>
# include "keys.h"

# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERS 150
# define ZOOM_STEP 0.7
# define MOVE_STEP 5

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_fractol
{
	int			(*formula)(t_complex pos, struct s_fractol *fractol);
	t_complex	c;
	t_mlx		*mlx;
	t_complex	corner;
	double		zoom;
	int			color;
	int			**depth;
}	t_fractol;

static t_complex	get_pos(size_t w, size_t h, t_fractol *fractol);
static int			get_color(int depth, int max_depth, int color);
void				paint(t_fractol *fractol);
void				draw(t_fractol *fractol);
int					julia(t_complex pos, t_fractol *fractol);
int					mandelbrot(t_complex pos, t_fractol *fractol);
int					burning_ship(t_complex pos, t_fractol *fractol);
static	int			mouse_handler(int button, int x, int y, void *param);
static int			key_handler2(int key_code, t_fractol *frac);
static int			key_handler(int key_code, t_fractol *param);
t_mlx				*init(t_fractol *fractol);
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void				write_help(void);
void				write_types(void);
void				free_depth(t_fractol *fractol);
int					free_all(t_fractol *fractol);
static double		den(long long n);
static	double		ft_atod(char *s);
static void			initialize(t_fractol *fractol);
t_fractol			*parse(int argc, char **argv);
int					create_trgb(int t, int r, int g, int b);
t_complex			init_complex(double real, double imag);
int					ft_streq(char *s1, const char *s2);
size_t				ft_strlen(const char *s);
void				ft_putsr_fd(char *s, int fd);
int					main(int argc, char **argv);
long long			ft_atol(const char *str);

#endif