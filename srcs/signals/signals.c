/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:36 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/30 10:53:58 by malaoui          ###   ########.fr       */
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
		write(STDOUT, "\033[0;32m\n", ft_strlen("\033[0;32m\n"));
		write(STDOUT, s, ft_strlen(s));
		write(STDOUT, " $ ", ft_strlen(" $ "));
		write(STDOUT, "\033[0m", ft_strlen("\033[0m"));
		g_signal_c = 1;
		if (g_line)
		{
			free(g_line);
			g_line = ft_strdup("");
		}
		g_saved = NULL;
	}
	if (signal == SIGQUIT)
	{
		if (g_child > 0)
			if (kill(g_child, 0) == 0)
				kill(g_child, SIGQUIT);
	}
}
