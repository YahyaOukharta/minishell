/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:54:38 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/13 15:39:35 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include "t_convs.h"
# include "get_specifiers.h"
# include "precision.h"
# include "min_width.h"
# include <stdio.h>

int		ft_printf(const char *format, ...);
void	ft_swap(char *a, char *b);
int		index_of(char c, const char *str);
char	*take_out(char *flgs, char f);
void	free_specifiers(char *flags, char *min_width, char *prec, char **tab);
char	*get_star_param(va_list args, char *old_param);
char	*get_arg_value(va_list args, char t_conv, const char *t_convs);
char	*add_precision(char *arg, char t_conv, char *p, const char *t_convs);
char	*process_precision(char *precision, va_list args);
char	*process_min_width(char *min_width, char **flags, va_list args);
char	*add_padding(char *arg, char t_conv, char *width, const char *flags);
char	**process_arg(char *c, va_list a, const char *t_cvs, const char *flags);

#endif
