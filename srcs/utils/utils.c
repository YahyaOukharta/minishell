/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:49 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/21 10:10:59 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_and_return(void *ptr, void *ret)
{
	free(ptr);
	return (ret);
}

int		string_equal(char *s1, char *s2)
{
	int res;

	res = ft_strncmp(s1, s2, max_v(ft_strlen(s1), ft_strlen(s2)));
	return (res == 0);
}

int		is_blank(char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

int		is_number(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && (i != 0 || (s[0] != '-' && s[0] == '+')))
			return (0);
		i++;
	}
	return (1);
}

char	*get_cwd(char *s, int size)
{
	ft_bzero(s, size);
	getcwd(s, size);
	return (s);
}
