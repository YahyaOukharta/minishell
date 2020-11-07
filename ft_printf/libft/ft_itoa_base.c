/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 05:05:49 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/29 05:25:29 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_digits_base(unsigned long long n, size_t base)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(unsigned long long n, const char *base)
{
	char				*res;
	unsigned long long	nbr;
	int					negative;
	size_t				n_digits;
	int					i;

	negative = 0;
	nbr = n;
	n_digits = count_digits_base(nbr, ft_strlen(base));
	res = (char *)malloc(sizeof(char) * (n_digits + negative + 1));
	if (!res)
		return (0);
	if (negative)
		res[0] = '-';
	i = n_digits;
	while (i > 0)
	{
		res[i + negative - 1] = base[nbr % ft_strlen(base)];
		nbr /= ft_strlen(base);
		i--;
	}
	res[n_digits + negative] = '\0';
	return (res);
}
