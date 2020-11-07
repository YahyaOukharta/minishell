/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:46:37 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:49:39 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRECISION_H
# define PRECISION_H
# include "ft_printf.h"

char	*add_precision_c(char *arg, char *precision);
char	*add_precision_s(char *arg, char *precision);
char	*add_precision_ptr(char *arg, char *precision);
char	*add_precision_int(char *arg, char *precision);
char	*add_precision_uint(char *arg, char *precision);
char	*add_precision_hex(char *arg, char *precision);
char	*add_precision_percent_sign(char *arg, char *precision);
void	init_p_dispatcher(void);
typedef	char*(*t_p_disp)(char *, char *);
t_p_disp g_p_dispatcher[11];
#endif
