/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:36:56 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 16:14:41 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int			count_digits(const char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	if (*str == '.')
		str++;
	else
		return (i);
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	return (i);
}

static int			check_overflow(float res, int sign)
{
	if (res * sign > 0 && sign < 0)
		return (0);
	else if (res * sign < 0 && sign > 0)
		return (-1);
	return (1);
}

static char			*skip_whitespace(char *str, int *sign)
{
	*sign = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	return (str);
}

float				ft_atof(char *str)
{
	float	res;
	int		vars[4];

	vars[3] = 0;
	res = 0;
	str = skip_whitespace(str, &vars[0]);
	if (!ft_strchr(str, '.'))
		return ((float)(ft_atoi(str) * vars[0]));
	vars[1] = count_digits(str);
	while (ft_isdigit(*str))
	{
		res = (res * 10) + *str - '0';
		vars[3]++;
		str++;
		if (*str == '.')
		{
			vars[2] = vars[1] - vars[3];
			str++;
		}
	}
	if ((vars[3] = check_overflow(res, vars[0])) == 1)
		return ((float)(res / (float)pow(10, vars[2])) * vars[0]);
	else
		return (vars[3]);
}

float				ft_set_precision(float n, int prec)
{
	return (floor(pow(10, prec) * n) / pow(10, prec));
}
