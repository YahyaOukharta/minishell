/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:48 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/19 18:49:29 by malaoui          ###   ########.fr       */
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
		{
			g_status = 2;
			g_return = 2;
			continue ;
		}
		free_pipeline(parsed_line);
		(g_saved != NULL) ? free(g_saved) : 0;
	}
	free_env();
	g_return = (g_status != -1) ? g_status : g_return;
}

void		ft_minishell_test(char **env, char *line)
{
	int			rt;
	t_pipeline	**parsed_line;

	rt = 0;
	init_shell(env);
	g_signal_bs = 0;
	if (!(parsed_line = parse_data(line)))
	{
		g_status = 2;
		g_return = 2;
		return ;
	}
	free_pipeline(parsed_line);
	if (g_saved)
		free(g_saved);
	free_env();
	if (g_status != -1)
		g_return = g_status;
}

int			main(int ac, char **argv, char **env)
{
	if (ac == 1)
		ft_minishell(env);
	else if (ac == 3 && string_equal(argv[1], "-c"))
		ft_minishell_test(env, ft_strdup(argv[2]));
	else
		ft_putstr_fd("Usage : ./minishell\n", STDERR);
	return (g_return);
}
