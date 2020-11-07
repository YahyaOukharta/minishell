/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:24:38 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 15:24:40 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_star_param(va_list args, char *old_param)
{
	char	*res;

	res = ft_itoa(va_arg(args, int));
	free(old_param);
	return (res);
}

char	*get_arg_value(va_list args, char t_conv, const char *t_convs)
{
	int	index;

	index = index_of(t_conv, t_convs);
	if (index > -1)
		return (g_t_dispatcher[index](args));
	else
		return (0);
}

char	*add_padding(char *arg, char t_conv, char *width, const char *flags)
{
	int		index;
	char	*res;

	index = index_of(t_conv, "cspdiuxX%");
	res = g_w_dispatcher[index](arg, width, flags);
	return (res);
}

char	*add_precision(char *arg, char t_conv, char *p, const char *t_convs)
{
	char	*res;
	int		index;

	if (!p || ft_atoi(p) < 0)
		return (arg);
	index = index_of(t_conv, t_convs);
	res = g_p_dispatcher[index](arg, p);
	return (res);
}

void	free_specifiers(char *flags, char *min_width, char *p, char **tab)
{
	if (tab)
	{
		free(tab[0]);
		free(tab[1]);
		free(tab[2]);
		free(tab[3]);
		free(tab);
	}
	free(flags);
	free(p);
	free(min_width);
}
