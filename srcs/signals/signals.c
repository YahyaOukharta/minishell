/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:36 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/20 17:12:05 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	s[1024];

	ft_bzero(s, 1000);
	getcwd(s, 1000);
	write(STDOUT, "\b\033[0;32m\n\r", ft_strlen("\b\033[0;32m\n\r"));
	write(STDOUT, s, ft_strlen(s));
	write(STDOUT, " $ ", ft_strlen(" $ "));
	write(STDOUT, "\033[0m", ft_strlen("\033[0m"));
}

void	signal_handler(int signal)
{
	if (signal == SIGINT && (g_child == 0))
	{
		prompt();
		g_signal_c = 1;
		if (g_line != NULL)
		{
			free(g_line);
			g_line = NULL;
		}
		free(g_saved);
		g_saved = NULL;
	}
	if (signal == SIGQUIT)
	{
		if (g_child > 0)
		{
			if (kill(g_child, 0) == 0)
				kill(g_child, SIGQUIT);
		}
	}
}
