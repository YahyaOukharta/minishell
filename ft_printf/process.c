/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:08:02 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 15:08:10 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*process_min_width(char *min_width, char **flags, va_list args)
{
	char	*tmp;

	if (min_width && !ft_strncmp(min_width, "*", ft_strlen(min_width)))
	{
		min_width = get_star_param(args, min_width);
		if (ft_atoi(min_width) < 0)
		{
			tmp = min_width;
			min_width = ft_substr(min_width, 1, ft_strlen(min_width) - 1);
			free(tmp);
			tmp = ft_strdup("-");
			free(*flags);
			*flags = tmp;
		}
	}
	return (min_width);
}

char	*process_precision(char *precision, va_list args)
{
	if (precision && !ft_strncmp(precision, "*", ft_strlen(precision)))
		precision = get_star_param(args, precision);
	return (precision);
}

char	**process_arg(char *c, va_list args, const char *t_cs, const char *f)
{
	char *res;
	char *flags;
	char *min_width;
	char *precision;
	char **tab;

	tab = (char **)malloc(sizeof(char *) * (3 + 1));
	tab[3] = 0;
	flags = get_flags(c, f);
	precision = get_precision(c, t_cs);
	min_width = get_min_width(c, f);
	min_width = process_min_width(min_width, &flags, args);
	precision = process_precision(precision, args);
	res = get_arg_value(args, c[strlen(c) - 1], t_cs);
	tab[1] = ft_strdup(res);
	if (precision)
		res = add_precision(res, c[strlen(c) - 1], precision, t_cs);
	if (precision && flags && c[strlen(c) - 1] != 's'
			&& c[strlen(c) - 1] != 'c')
		flags = take_out(flags, '0');
	res = add_padding(res, c[strlen(c) - 1], min_width, flags);
	tab[2] = (flags ? ft_strdup(flags) : ft_strdup(""));
	free_specifiers(flags, min_width, precision, NULL);
	tab[0] = res;
	return (tab);
}
