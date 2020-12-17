#include "minishell.h"

int			ft_prompt(char *msg, char **line)
{
	if (g_signal_c == 1)
	{
		ft_putchar_fd('\r', STDOUT);
		g_signal_c = 0;
	}
	if (g_signal_d == 1)
	{
		ft_putstr_fd(msg, STDOUT);
		ft_putstr_fd(" $ ", STDOUT);
	}
	ft_printf("\033[0m");
	return (get_next_line(STDIN, line));
}

void		ft_minishell(char **env)
{
	char	*line;
	char	cwd[1024];
	int		rt;
	int		i;
	char	*checked_line;
	t_pipeline **parsed_line;

	rt = 0;
	init_environment(env);
	init_builtins();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_status = 0;
	g_signal_c = 0;
	g_signal_d = 1;
	while (g_status != -1)
	{
		line = NULL;
		getcwd(cwd, 1000);
		ft_printf("\n\033[0;32m");
		rt = ft_prompt(cwd, &line);
		if (rt == 0)
		{
			if (ft_strlen(line))
			{
				free(line);
				line = NULL;
				g_signal_d = 0;
				continue ;
			}
			else
				exit(1);
		}
		g_signal_d = 1;
		if (!(checked_line = check_line(line)))
		{
			free(line);
			continue ;
		}
		parsed_line = parser(checked_line);
		print_parsed_line(parsed_line);
		i = 0;
		while (parsed_line[i])
		{
			g_status = execute_pipeline(parsed_line[i]);
			i++;
		}
		free(line);
		line = NULL;
	}
}

int			main(int ac, char **argv, char **env)
{
	if (ac == 1)
		ft_minishell(env);
	else
		ft_printf("Usage : ./minishell\n");
	return (0);
}
