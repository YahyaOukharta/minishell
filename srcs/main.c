/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:48 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/30 11:56:31 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_line(char **line)
{
	char	*tmp;

	tmp = ft_strdup(*line);
	if (*line)
		free(*line);
	*line = ft_strjoin(g_saved, tmp);
	if (g_saved)
		free(g_saved);
	if (tmp)
		free(tmp);
	g_saved = NULL;
	g_exec = 0;
}

void		ft_minishell(char **env)
{
	int			rt;
	t_pipeline	**parsed_line;

	rt = 0;
	init_shell(env);
	while (g_status != -1)
	{
		g_signal_bs = 0;
		g_line = NULL;
		rt = ft_prompt(&g_line);
		if (handle_return(rt, g_line) == true)
			continue ;
		if ((g_exec && rt))
			set_line(&g_line);
		if (!(parsed_line = parse_data(g_line)))
			continue ;
		print_parsed_line(parsed_line);
		exec_parsed(parsed_line);
		free_pipeline(parsed_line);
		if (g_saved)
			free(g_saved);
	}
	free_env();
}

int			main(int ac, char **argv, char **env)
{
	(void)argv;
	if (ac == 1)
		ft_minishell(env);
	else
		ft_putstr_fd("Usage : ./minishell\n", STDERR);
	return (g_return);
}