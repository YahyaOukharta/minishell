/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:36 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/20 14:39:38 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	char	s[1024];

	ft_bzero(s, 1000);
	getcwd(s, 1000);
	if (signal == SIGINT)
	{
		if (g_child == 0)
		{
			write(STDOUT, "\b\033[0;32m\n\r", ft_strlen("\b\033[0;32m\n\r"));
			write(STDOUT, s, ft_strlen(s));
			write(STDOUT, " $ ", ft_strlen(" $ "));
			write(STDOUT, "\033[0m", ft_strlen("\033[0m"));
			g_signal_c = 1;
			if (g_line != NULL)
				g_line = NULL;
			g_saved = NULL;
		}
	}
	if (signal == SIGQUIT)
	{
		if (g_child > 0)
		{
			if (kill(g_child, 0) == 0)
			{
				kill(g_child, SIGQUIT);
				ft_putstr_fd("Quit ..!\n\b", 1);
			}
		}
		else
			ft_putstr_fd("\b\b  \b\b", STDERR);
	}
}
