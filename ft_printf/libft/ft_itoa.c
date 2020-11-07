/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:41:37 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/20 18:04:33 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long long n)
{
	int	res;

	if (n == 0)
		return (1);
	res = 0;
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (str)
	{
		i = 0;
		j = ft_strlen(str) - 1;
		while (i < j)
		{
			tmp = str[i];
			str[i] = str[j];
			str[j] = tmp;
			i++;
			j--;
		}
	}
	return (str);
}

void		ft_store(char *s, long n, size_t ndigits)
{
	size_t i;

	i = 0;
	while (i < ndigits)
	{
		s[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	ft_strrev(s);
}

char		*ft_itoa(int nbr)
{
	long long	n;
	char		*result;
	int			negative;
	int			n_digits;

	n = nbr;
	negative = 0;
	if (nbr < 0)
	{
		n = (long)nbr * -1;
		negative = 1;
	}
	n_digits = count_digits(n);
	result = (char *)malloc(sizeof(char) * (negative + n_digits + 1));
	if (!result)
		return (0);
	if (negative)
		result[0] = '-';
	result[n_digits + negative] = '\0';
	ft_store(result + negative, n, n_digits);
	return (result);
}
