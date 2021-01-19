/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:02:30 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/19 08:02:42 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checker(char *s)
{
	int i;

	i = 2;
	if (!(ft_strncmp("-n", s, 2)))
	{
		while (i < (int)ft_strlen(s))
			if (s[i++] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

int		isallnum(char *s)
{
	int i;
	int len;
	int flag;
	int	sign;

	i = 0;
	len = ft_strlen(s);
	flag = 0;
	sign = 0;
	while (i < len)
	{
		if (s[i] == '-' || s[i] == '+')
		{
			sign++;
			i++;
		}
		if (sign > 1)
			return (0);
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*skip_blank(char *s)
{
	while (*s && is_blank(*s))
		s++;
	return (s);
}

int		isallalphanum(char *s)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*is_special(char c)
{
	return (ft_strchr("$\\\"", c));
}
