/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:53:46 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/11 19:18:14 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t n)
{
	unsigned char *dest;

	dest = (unsigned char *)ptr;
	while (n > 0)
	{
		*dest = (unsigned char)value;
		dest++;
		n--;
	}
	return (ptr);
}
