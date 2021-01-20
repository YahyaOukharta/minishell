/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:01 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/19 19:15:54 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_prompt(char **line)
{
	char	cwd[1024];

	ft_bzero(cwd, 1000);
	getcwd(cwd, 1000);
	ft_putstr_fd("\033[0;32m", STDOUT);
	if (g_signal_c == 1)
	{
		ft_putchar_fd('\r', STDOUT);
		g_signal_c = 0;
	}
	if (g_signal_d == 1)
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd(" $ ", STDOUT);
	}
	ft_putstr_fd("\033[0m", STDOUT);
	return (get_next_line(STDIN, line));
}

void			init_shell(char **env)
{
	char	*s;
	t_env	*shlvl;

	s = ft_calloc(1000, 1);
	getcwd(s, 999);
	init_environment(env);
	shlvl = env_with_key("SHLVL");
	set_env("PWD", s);
	if (shlvl != NULL)
		set_env("SHLVL", ft_itoa(ft_atoi(shlvl->value) + 1));
	else
		set_env("SHLVL", "1");
	set_env("_", ft_strjoin(s, "/minishell"));
	init_builtins();
	g_status = 0;
	g_signal_c = 0;
	g_signal_d = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

bool			handle_return(int rt, char *line)
{
	char		*tmp;

	if (rt == 0)
	{
		if (ft_strlen(line))
		{
			tmp = ft_strdup(g_saved);
			g_exec = 1;
			if (g_saved)
				free(g_saved);
			g_saved = ft_strjoin(tmp, line);
			if (tmp)
				free(tmp);
			free(line);
			line = NULL;
			g_signal_d = 0;
			return (true);
		}
		free(g_line);
		free(g_saved);
		ft_putchar_fd('\n', STDOUT);
		exit(1);
	}
	g_signal_d = 1;
	return (false);
}

t_pipeline		**parse_data(char *line)
{
	char		*checked_line;
	t_pipeline	**parsed_line;

	checked_line = NULL;
	if (!(checked_line = check_line(line)))
	{
		g_status = 2;
		free(line);
		return (NULL);
	}
	parsed_line = parser(checked_line);
	if (checked_line)
		free(checked_line);
	return (parsed_line);
}

void			exec_parsed(t_pipeline **parsed_line)
{
	int i;

	i = 0;
	while (parsed_line[i] != NULL && g_status != -1)
	{
		if (parsed_line[i]->cmds)
			g_status = execute_pipeline(parsed_line[i]);
		i++;
	}
}
