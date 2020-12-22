#include "minishell.h"

void		free_cmds(t_command **cmd)
{
	int 	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i]->tokens)
			free_s_tab(cmd[i]->tokens);
		if (cmd[i]->input_files)
			free_s_tab(cmd[i]->input_files);
		if (cmd[i]->output_files)
			free_s_tab(cmd[i]->output_files);
		i++;
	}
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
		i++;
	}
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
}

void		ft_minishell(char **env)
{
	char		*line;
	int			rt;
	t_pipeline	**parsed_line;

	rt = 0;
	init_shell(env);
	while (g_status != -1)
	{
		line = NULL;
		rt = ft_prompt(&line);
		if (handle_return(rt, line) == true)
			continue ;
		if (!(parsed_line = parse_data(line)))
			continue ;
		exec_parsed(parsed_line);
		free_pipeline(parsed_line);
		free(line);
	}
	free_shell();
}

int			main(int ac, char **argv, char **env)
{
	if (ac == 1)
		ft_minishell(env);
	else
		ft_printf("Usage : ./minishell\n");
	return (0);
}
