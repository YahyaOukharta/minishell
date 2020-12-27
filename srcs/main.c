/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:48 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/27 15:52:55 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_cmds(t_command **cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i]->tokens)
			free_s_tab(cmd[i]->tokens);
		if (cmd[i]->input_files)
			free_s_tab(cmd[i]->input_files);
		if (cmd[i]->output_files)
			free_s_tab(cmd[i]->output_files);
		free(cmd[i]);
		i++;
	}
	free(cmd[i]);
	free(cmd);
}

void		free_pipeline(t_pipeline **p)
{
	int 	i;

	i = 0;
	while (p[i] != NULL)
	{
		if (p[i]->cmds)
			free_cmds(p[i]->cmds);
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
}

void		free_shell()
{
	int		i;

	i = 0;
	while (g_env != NULL)
	{
		free(g_env->key);
		free(g_env->value);
		g_env = g_env->next;
	}
	//system("leaks minishell");
}

void		set_line(char	**line)
{
	char	*tmp;

	//if (*line)
	tmp = ft_strdup(*line);
	//if (*line)
	//	free(*line);
	*line = ft_strjoin(g_saved, tmp);
	if (g_saved)
		free(g_saved);
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
		g_line = NULL;
		rt = ft_prompt(&g_line);
		if (handle_return(rt, g_line) == true)
			continue ;
		if (g_exec && rt)
			set_line(&g_line);
		if (!(parsed_line = parse_data(g_line)))
			continue ;
		print_parsed_line(parsed_line);
		exec_parsed(parsed_line);
		free_pipeline(parsed_line);
	}
	free_shell();
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
