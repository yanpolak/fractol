/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:29:05 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/22 17:29:39 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (c >= 9 && c <= 13);
}

static int	ft_skip(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	return (i);
}

static long long	ft_check_overflow(long long ans, int digit)
{
	if (ans > LONG_MAX / 10 || (ans == LONG_MAX / 10 && digit > 7))
		return (LONG_MAX);
	if (ans < LONG_MIN / 10 || (ans == LONG_MIN / 10 && digit > 8))
		return (LONG_MIN);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	ans;
	int			i;
	int			sign;

	ans = 0;
	sign = 1;
	i = ft_skip(str, &sign);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (ft_check_overflow(ans, sign * (str[i] - '0')))
			return ((int)ft_check_overflow(ans, sign * (str[i] - '0')));
		ans = ans * 10 + sign * (str[i] - '0');
		if (ans > 0 && sign < 0)
			ans *= -1;
		++i;
	}
	return (ans);
}
