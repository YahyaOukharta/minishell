/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:22:20 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/23 01:26:42 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

char	*ft_ftoa(float n, size_t precision)
{
	char	*res;
	int		i_part;
	float	f_part;
	char	*sign;
	char	*tmp;

	i_part = (int)n;
	f_part = (float)i_part - (float)n;
	if (i_part < 0)
		i_part *= -1;
	if (f_part < 0)
		f_part *= -1.0;
	sign = (n < 0 ? "-" : "");
	tmp = ft_itoa(i_part);
	res = ft_strjoin(sign, tmp);
	free(tmp);
	if (precision)
	{
		tmp = ft_itoa((int)(f_part * pow(10, precision)));
		sign = res;
		res = ft_strjoin_va(3, res, ".", tmp);
		free(sign);
		free(tmp);
	}
	return (res);
}
