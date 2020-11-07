/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:09:50 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 16:10:22 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_digits(unsigned int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	char	*res;
	size_t	n_digits;
	size_t	i;

	n_digits = count_digits(n);
	res = malloc(sizeof(char) * (n_digits + 1));
	i = n_digits;
	while (i > 0)
	{
		res[i - 1] = n % 10 + '0';
		n /= 10;
		i--;
	}
	res[n_digits] = '\0';
	return (res);
}
